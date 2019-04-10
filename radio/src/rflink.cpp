/*
 * rflink.cpp
 *
 *  Created on: Nov 9, 2018
 *      Author: bodri
 */

#include "rflink.h"
#include "spi.h"

#include <array>
#include <vector>

void RfLink::init() {
	this->patternGenerator = new PatternGenerator(NULL, PatternGenerator::maximumNumberOfChannels);
	Pin nresetPin(RF1NRESET_GPIO_Port, RF1NRESET_Pin);
	Pin ncsPin(RF1NSS_GPIO_Port, RF1NSS_Pin);
	Pin busyPin(RF1BUSY_GPIO_Port, RF1BUSY_Pin);
	this->rf1Module = new SX1280(&hspi1, nresetPin, ncsPin, busyPin);

	rf1Module->onTxDone = [this]() {
//		HAL_GPIO_WritePin(RF1TxEnable_GPIO_Port, RF1TxEnable_Pin, GPIO_PIN_RESET);
		state = TRANSMITTED;
	};

	rf1Module->onSyncWordDone = [this]() {
	    state = SYNC_RECEIVED;
	};

	rf1Module->onRxDone = [this]() {
//		HAL_GPIO_WritePin(RxEnable_GPIO_Port, RxEnable_Pin, GPIO_PIN_RESET);
		state = RECEIVED;
	};

	rf1Module->init();
	rf1Module->setAddress(0x6969);

    if (transmitter) {
    	uint16_t txIrqMask { IRQ_TX_DONE };
    	rf1Module->setDioIrqParams(txIrqMask, txIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE);
    } else {
    	uint16_t rxIrqMask { IRQ_RX_DONE | IRQ_SYNCWORD_VALID };
    	rf1Module->setDioIrqParams(rxIrqMask, rxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE);
	}

    __HAL_TIM_SET_AUTORELOAD(heartBeatTimer, transmitter ? trackingHopRate : acqusitionHopRate);
}

void RfLink::processHeartBeat(TIM_HandleTypeDef *htim) {
	if (htim != heartBeatTimer) { return; }

	heartBeatTimeout = true;
}

void RfLink::processIrqs(Pin  pin) {
//	static const Pin irqPin(RF1IRQ_GPIO_Port, RF1IRQ_Pin);
//	if (pin == irqPin) {
//		lastIrqSource = MODULE1_IRQ;
//	}
}

void RfLink::runLoop(void) {

	if (lastIrqSource != NO_IRQ) {
		// 56 us
		if (lastIrqSource == MODULE1_IRQ) {
			rf1Module->processIrqs();
		} else {

		}

		lastIrqSource = NO_IRQ;
	}

	if (heartBeatTimeout) {
		// tracking: 28 us, acquisition: ~140us
//		HAL_GPIO_WritePin(Heartbeat_GPIO_Port, Heartbeat_Pin, GPIO_PIN_SET);
//		LL_IWDG_ReloadCounter(IWDG);
		heartBeatTimeout = false;
		HAL_SPI_Abort(&hspi1);
//		HAL_GPIO_WritePin(RF1CS_GPIO_Port, RF1CS_Pin, GPIO_PIN_SET);

		rf1Module->standBy();

		if (state != WAITING_FOR_NEXT_HOP) {
			// 70 us
			registerLostPacket();
		}

		state = START;
//		HAL_GPIO_WritePin(Heartbeat_GPIO_Port, Heartbeat_Pin, GPIO_PIN_RESET);
	}

	switch (state) {
	case START:
		// 49 us
		packetNumber++;
		if (packetNumber >= 1000) {
			packetNumber = 0;
		}
		rf1Module->setChannel(patternGenerator->nextHop());
		state = SEND_OR_ENTER_RX;
		break;
	case SEND_OR_ENTER_RX:
		// sendPacket xxx us, enterRx: 153 us
		upLink() ? sendPacket() : enterRx();
		state = WAITING_FOR_SYNC;
		break;
	case TRANSMITTED:
		state = DONE;
		break;
	case SYNC_RECEIVED:
		lostSync = 0;
	    adjustTimerToTrackTx();
	    state = WAITING_FOR_RECEIVE;
	    break;
	case RECEIVED: {
		// xxx us
		lostPacket = 0;

		uint8_t payload[127];
		uint8_t maxSize = sizeof(payload);
		uint8_t size;
		memset(payload, 0, 127);
		rf1Module->getPayload(payload, &size, maxSize);
		if (size == 41) {
			Packet packet;
			memcpy(&packet.status, &payload[0], 2);
			memcpy(&packet.payload[0], &payload[2], 6);
			onReceive(packet);
		}
		state = DONE;
	}
		break;
	case DONE:
//		if (packetNumber == 255) {
//			float per = (float)failuresPerChannel[patternGenerator->currentChannel()];
//			for (int i = 0; i < 10; i++) { }
//		}

//		setTracking(tracking);
//		if (lostPacket > 0) {
//			printf("%lu lost packet(s)!\n", lostPacket);
//			lostPacket = 0;
//		}

//		Packet *packet = rf1Buffer.current;
//
//		if (packet->payload.packetNumber == 100) {
//			printf("Packet: %.20s\n", packet->payload.buffer);
//		}
//
//		printf("Packet %d, RSSI: %ddBm, lqi: %d%%\n",
//				packet->payload.packetNumber, rssiPowerLevel(packet->status.rssi),
//				lqiPercentage(packet->status.linkQuality.lqi));
		state = WAITING_FOR_NEXT_HOP;
		break;
	default:
		break;
	}
}

//
// Private methods
//

bool RfLink::upLink(void) {
	if (tracking) {
		// Every 4th hop is a down-link
//		return ((transmitter && packetNumber % 4) || (!transmitter && !(packetNumber % 4)));
		return transmitter;
	} else {
		// no down-link during acquisition
		return transmitter;
	}
}

void RfLink::setTracking(bool tracking) {
	if (this->tracking != tracking) {
		this->tracking = tracking;

//			printf("Transciever mode: ");
		if (tracking) {
//				printf("TRACKING\n");
//			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
			if (!transmitter) {
				__HAL_TIM_SET_AUTORELOAD(heartBeatTimer, trackingHopRate);
			}
		} else {
//				printf("ACQUSITION\n");
//			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			if (!transmitter) {
				__HAL_TIM_SET_AUTORELOAD(heartBeatTimer, transmitter ? trackingHopRate : acqusitionHopRate);
			}
		}
	}
}

void RfLink::adjustTimerToTrackTx(void) {
	__HAL_TIM_SET_COUNTER(heartBeatTimer, timerWhenSynReceived);
	setTracking(true);
}

void RfLink::registerLostPacket(void) {
	lostSync++;
	lostPacket++;

	if (lostSync > transmitter ? lostSyncTreshold / downLinkFrequency : lostSyncTreshold) {
		setTracking(false);
		auto currentChannel = patternGenerator->currentChannel();
		auto item = failuresPerChannel.find(currentChannel);
		if (item != failuresPerChannel.end()) {
			failuresPerChannel[currentChannel]++;
		} else {
			failuresPerChannel[currentChannel] = 1;
		}
	}
}

void RfLink::sendPacket(void) {
//    HAL_GPIO_WritePin(RF1TxEnable_GPIO_Port, RF1TxEnable_Pin, GPIO_PIN_SET);
    Packet packet { 0 };
    packet.status.packetNumber = packetNumber;
    onTransmit(packet);
    rf1Module->send((uint8_t *)&packet, sizeof(Packet));
}

void RfLink::enterRx(void) {
//    HAL_GPIO_WritePin(RxEnable_GPIO_Port, RxEnable_Pin, GPIO_PIN_SET);
    rf1Module->enterRx();
}
