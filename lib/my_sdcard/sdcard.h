#ifndef SDCARD_H
#define SDCARD_H


#include "stm32f407xx.h"
//#include "fatfs.h"



//-------- SDIO pinout----------------
// WARNING: if SDIO pinout changed, then SD_GPIO_Init() nust be edit
#define SDIO_PORT			GPIOC
#define SDIO_CMD_PORT		GPIOD
#define SD_CD_PORT			GPIOD

#define SDIO_D0_PIN_NUM			8
#define SDIO_D1_PIN_NUM			9
#define SDIO_D2_PIN_NUM			10
#define SDIO_D3_PIN_NUM			11
#define SDIO_CLK_PIN_NUM		12
#define SDIO_CMD_PIN_NUM		2

#define SD_CD_PIN_NUM			3	// card persence pin


#define SD_CD_CHECK()	( SD_CD_PORT->IDR & ( 1 << SD_CD_PIN_NUM) )



void SDIO_GPIO_Init(void); // SDCard GPIO init

void SD_Card_Init(void);	// SD_Card init

void SDIO_Init(void);	// SDIO modue init and configuration

uint8_t SD_power_ON(void);	// SD card power on

uint8_t SD_InitCard(void);	// SD card initialization

void SDIO_ModuleConfig(void);	// SDIO module configuration

// SDcard operation functions








#endif