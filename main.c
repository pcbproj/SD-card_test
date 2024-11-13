/*******************************************************************/
#include "main.h"



/*******************************************************************/
#define BUFFER_SIZE		(uint16_t)64 // ascii table in 32-bit words length




uint32_t writeBuffer[BUFFER_SIZE]; 
uint32_t readBuffer[BUFFER_SIZE];

uint8_t readData_8[BUFFER_SIZE * 4];
uint8_t writeBuffer_bytes[BUFFER_SIZE * 4];



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

	for (uint16_t i = 0; i < BUFFER_SIZE*4; i++){
		writeBuffer_bytes[i] = (i + chr);
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
    	// запись блока данных
    	//SD_WriteBlockBytes(0x00000000, writeBuffer_bytes, SD_BLOCK_SIZE_BYTES);
		
		//disk_write (0, writeBuffer_bytes, 0x00000000, 1);
		
		printf("----- SD-card Block %d bytes reading! ---- \n", BUFFER_SIZE*4);
		// чтение блока данных
		//SD_ErrorState = SD_ReadBlockBytes(0x00000000, readData_8, SD_BLOCK_SIZE_BYTES);
		disk_read(0, readData_8, 0x00000000, 1);

		
		if(SD_ErrorState == SD_OK) usart1_send(readData_8, BUFFER_SIZE*4);
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

	