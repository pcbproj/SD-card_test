#include "sdcard_my.h"

// sdcard_sdio.c  sdcard_sdio.h

void SD_Card_Init(void){
	
	SDIO_GPIO_Init();

	SDIO_Init();

}


void SDIO_GPIO_Init(void){
RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	
	// Make sure that all SDIO GPIO pins are internally, or externally, pulled-up except for the CLK line
	SDIO_PORT -> PUPDR |= ( 1 << (SDIO_D0_PIN_NUM *2) );
	SDIO_PORT -> PUPDR |= ( 1 << (SDIO_D1_PIN_NUM *2) );
	SDIO_PORT -> PUPDR |= ( 1 << (SDIO_D2_PIN_NUM *2) );
	SDIO_PORT -> PUPDR |= ( 1 << (SDIO_D3_PIN_NUM *2) );
	SDIO_CMD_PORT -> PUPDR |= ( 1 << (SDIO_CMD_PIN_NUM *2) );
	
	SD_CD_PORT -> PUPDR |= ( 1 << (SD_CD_PIN_NUM *2) );

	
	// enable alternative function for SDIO pins
	SDIO_PORT -> MODER |= (1 << ( (SDIO_D0_PIN_NUM *2) + 1) );
	SDIO_PORT -> MODER |= (1 << ( (SDIO_D1_PIN_NUM *2) + 1) );
	SDIO_PORT -> MODER |= (1 << ( (SDIO_D2_PIN_NUM *2) + 1) );
	SDIO_PORT -> MODER |= (1 << ( (SDIO_D3_PIN_NUM *2) + 1) );
	SDIO_PORT -> MODER |= (1 << ( (SDIO_CLK_PIN_NUM *2) + 1) );
	SDIO_CMD_PORT -> MODER |= (1 << ( (SDIO_CMD_PIN_NUM *2) + 1) );

	SD_CD_PORT -> MODER &= ~( 3 << (SD_CD_PIN_NUM *2) );		// SD_CD_PIN_NUM in input mode
	

	// maximum speed in output pins
	SDIO_PORT -> OSPEEDR |= ( 3 << (SDIO_D0_PIN_NUM *2) );
	SDIO_PORT -> OSPEEDR |= ( 3 << (SDIO_D1_PIN_NUM *2) );
	SDIO_PORT -> OSPEEDR |= ( 3 << (SDIO_D2_PIN_NUM *2) );
	SDIO_PORT -> OSPEEDR |= ( 3 << (SDIO_D3_PIN_NUM *2) );
	SDIO_PORT -> OSPEEDR |= ( 3 << (SDIO_CLK_PIN_NUM *2) );
	SDIO_CMD_PORT -> OSPEEDR |= ( 3 << (SDIO_CMD_PIN_NUM *2) );


	// select alternate function AF12 for SDIO-pins
	SDIO_PORT -> AFR[1] |= ( 12 << ( (SDIO_D0_PIN_NUM - 8)*4 ) );
	SDIO_PORT -> AFR[1] |= ( 12 << ( (SDIO_D1_PIN_NUM - 8)*4 ) );
	SDIO_PORT -> AFR[1] |= ( 12 << ( (SDIO_D2_PIN_NUM - 8)*4 ) );
	SDIO_PORT -> AFR[1] |= ( 12 << ( (SDIO_D3_PIN_NUM - 8)*4 ) );
	SDIO_PORT -> AFR[1] |= ( 12 << ( (SDIO_CLK_PIN_NUM - 8)*4 ) );
	SDIO_CMD_PORT -> AFR[0] |= ( 12 << ( (SDIO_CMD_PIN_NUM)*4 ) );
}




void SDIO_Init(void){

// SDIO module enable
	RCC->APB2ENR |= RCC_APB2ENR_SDIOEN;
	
	// NOTE: clock settings in RCC_Init.c APB2_CLK freq = 84 MHz
	// NOTE: SDIO_CK must be in range 187 kHz - 24 MHz
	SDIO->CLKCR |= SDIO_CLKCR_CLKEN |		// Clk enable
					SDIO_CLKCR_PWRSAV |		// SDCLK is only  enabled when the bus is active
					SDIO_CLKCR_CLKDIV |		// clock divide factor SDIO_CK = ABP2CLK / (2+1) = 84 MHz / 3 = 28 MHz
					SDIO_CLKCR_WIDBUS_0;	// 4 bits bus mode
	
	// SDIO power OFF
	SDIO->POWER &= ~( SDIO_POWER_PWRCTRL ); 

	//SD_power_ON();

	//SD_InitCard();

	//SDIO_ModuleConfig();
		
	
}



uint8_t SD_power_ON(void){
	/* Power ON Sequence -------------------------------------------------------*/
	/* Configure the SDIO peripheral */



  /* Set Power State to ON */



  /* Enable SDIO Clock */



  /* CMD0: GO_IDLE_STATE -------------------------------------------------------*/
  /* No CMD response required */




  /* CMD8: SEND_IF_COND --------------------------------------------------------*/
  /* Send CMD8 to verify SD card interface operating condition */
  /* Argument: - [31:12]: Reserved (shall be set to '0')
               - [11:8]: Supply Voltage (VHS) 0x1 (Range: 2.7-3.6 V)
               - [7:0]: Check Pattern (recommended 0xAA) */
  /* CMD Response: R7 */



}





uint8_t SD_InitCard(void){	// SD card initialization

}







void SDIO_ModuleConfig(void){	// SDIO module configuration
	// Clock
	// BusWidth
	// HW Flow Control ON/OFF
}

