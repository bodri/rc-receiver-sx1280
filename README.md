This is the firmware for the Rc receiver based on the SX1280 chipset. The hardware design can be found here: [Rc Receiver](https://github.com/bodri/RcReceiver)

# Project goals
* Handle both receiver and transmitter in one codeline
* FHSS (Frequency Hopping Spread Spectrum) system
* 80 channels (on normal ISM band: 2400 Mhz - 2483.5 Mhz), with 1MHz channel separation
* 100 Hz hopping frequency
* Fixed hopping sequence
* Simple acquisition and tracking between the transmitter and receiver
* No binding process the transmitter and receiver hard-bound together
* Fixed packet length
* Transmitter sends basic control functions
* At least 16; 12 bit channels
* Receiver can also send telemetry data back
  - RSSI (Received Signal Strength Indicator)
  - Receiver battery voltage
  - Built in GPS support
  - Extensible via UART port(s)
* OTA (Over the Air) firmware update

# Current status (April 11, 2019)
* The firmware is only using the RF module #1
* FHSS works
* Acquisition and tracking works
* Communication is only one way at the moment
* (Code is a bit messy, just made it work)
