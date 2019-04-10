/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_dma.h"
#include "stm32l4xx_hal_spi.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RF1NRESET_Pin GPIO_PIN_2
#define RF1NRESET_GPIO_Port GPIOE
#define RF1RXEN_Pin GPIO_PIN_3
#define RF1RXEN_GPIO_Port GPIOE
#define RF1TXEN_Pin GPIO_PIN_4
#define RF1TXEN_GPIO_Port GPIOE
#define RF1BUSY_Pin GPIO_PIN_5
#define RF1BUSY_GPIO_Port GPIOE
#define RF1IRQ_Pin GPIO_PIN_6
#define RF1IRQ_GPIO_Port GPIOE
#define RF1MISO_Pin GPIO_PIN_6
#define RF1MISO_GPIO_Port GPIOA
#define RF1MOSI_Pin GPIO_PIN_7
#define RF1MOSI_GPIO_Port GPIOA
#define LEDRED_Pin GPIO_PIN_7
#define LEDRED_GPIO_Port GPIOE
#define LEDGREEN_Pin GPIO_PIN_8
#define LEDGREEN_GPIO_Port GPIOE
#define LEDBLUE_Pin GPIO_PIN_9
#define LEDBLUE_GPIO_Port GPIOE
#define RF1NSS_Pin GPIO_PIN_12
#define RF1NSS_GPIO_Port GPIOE
#define RF1CLK_Pin GPIO_PIN_13
#define RF1CLK_GPIO_Port GPIOE
#define RF2MOSI_Pin GPIO_PIN_15
#define RF2MOSI_GPIO_Port GPIOB
#define GPSEN_Pin GPIO_PIN_8
#define GPSEN_GPIO_Port GPIOD
#define RF2NRESET_Pin GPIO_PIN_11
#define RF2NRESET_GPIO_Port GPIOD
#define RF2RXEN_Pin GPIO_PIN_12
#define RF2RXEN_GPIO_Port GPIOD
#define RF2TXEN_Pin GPIO_PIN_13
#define RF2TXEN_GPIO_Port GPIOD
#define RF2BUSY_Pin GPIO_PIN_14
#define RF2BUSY_GPIO_Port GPIOD
#define RF2IRQ_Pin GPIO_PIN_15
#define RF2IRQ_GPIO_Port GPIOD
#define CANRX_Pin GPIO_PIN_11
#define CANRX_GPIO_Port GPIOA
#define CANTX_Pin GPIO_PIN_12
#define CANTX_GPIO_Port GPIOA
#define RF2NSS_Pin GPIO_PIN_0
#define RF2NSS_GPIO_Port GPIOD
#define RF2CLK_Pin GPIO_PIN_1
#define RF2CLK_GPIO_Port GPIOD
#define RF2MISO_Pin GPIO_PIN_3
#define RF2MISO_GPIO_Port GPIOD
#define GPSTX_Pin GPIO_PIN_5
#define GPSTX_GPIO_Port GPIOD
#define GPSRX_Pin GPIO_PIN_6
#define GPSRX_GPIO_Port GPIOD
#define GPSPPS_Pin GPIO_PIN_7
#define GPSPPS_GPIO_Port GPIOD
#define RFPOWEREN_Pin GPIO_PIN_1
#define RFPOWEREN_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
