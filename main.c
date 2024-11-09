/*******************************************************************/
#include "main.h"



/*******************************************************************/
#define BUFFER_SIZE				64 // ascii table in 23-bit words length

#define SD_BLOCK_SIZE_BYTES		512


uint32_t writeBuffer[BUFFER_SIZE]; 
uint32_t readBuffer[BUFFER_SIZE];



SD_CardInfo SDCardInfo;



/*******************************************************************/
int main()
{
	SD_Error SD_ErrorState = SD_OK;	// SD SDIO error status


	RCC_Init();
	APP_GPIO_Init();
	USART1_Init();		// for debug baudrate = 115200

	uint8_t chr = 0x21;	// character ASCII-code for '!'
	

	// Тестовые данные для записи
    for (uint16_t i = 0; i < BUFFER_SIZE; i++)
    {
		uint32_t temp_word = 0;
		for (uint8_t byte_num = 0; byte_num < 4; byte_num++){
			temp_word |= ( chr << ( byte_num*8 ) );
			chr++;
		}
		writeBuffer[i] = temp_word;
		readBuffer[i] = 0;
    }	

	printf("---- System started! ---- \n");

	printf("----- SD-card initialization started! ---- \n");
    // Иницилизация карты
	SD_ErrorState = SD_Init();

	if (SD_ErrorState == SD_OK) {
	
		printf("----- SD-card Getting information! ---- \n");
    	// Получаем информацию о карте
    	SD_GetCardInfo(&SDCardInfo);
    	
		printf("----- SD-card Selecting! ---- \n");
    	// Выбор карты и настройка режима работы
    	SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
    	SD_SetDeviceMode(SD_POLLING_MODE);
    	
		printf("----- SD-card Block %d bytes writing! ---- \n", BUFFER_SIZE*4);
    	// И вот наконец-то запись и чтение
    	SD_WriteBlock(0x00000000, writeBuffer, SD_BLOCK_SIZE_BYTES);
		
		printf("----- SD-card Block %d bytes reading! ---- \n", BUFFER_SIZE*4);
		SD_ErrorState = SD_ReadBlock(0x00000000, readBuffer, SD_BLOCK_SIZE_BYTES);
		
		if(SD_ErrorState == SD_OK) usart1_send_w32(readBuffer, BUFFER_SIZE);
		else printf("----- SD-card reading error! ----- \n");
	}
	else{
		printf("----- SD-card not found!! ---- \n");
	}

	
	while(1)
	{
	}

	return 0;
}



/*******************************************************************/

	