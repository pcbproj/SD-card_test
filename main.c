/*******************************************************************/
#include "main.h"



/*******************************************************************/
#define BUFFER_SIZE_BYTES		(uint16_t)2048 

#define READED_BYTES			(uint16_t)512
#define START_SECTOR_NUM		(uint32_t)4		// потому что в секторах 0-3 хранится разметка FAT32
#define SECTORS_QUANTITY		(uint16_t)2

uint8_t readData_8[BUFFER_SIZE_BYTES];
uint8_t writeBuffer_bytes[BUFFER_SIZE_BYTES];


SD_CardInfo SDCardInfo;



/*******************************************************************/
int main()
{
	SD_Error SD_ErrorState = SD_OK;	// SD SDIO error status


	RCC_Init();
	APP_GPIO_Init();
	USART1_Init();		// for debug baudrate = 115200


	// Тестовые данные для записи
 	for (uint16_t i = 0; i < BUFFER_SIZE_BYTES; i++){
		writeBuffer_bytes[i] = (i & 0x00FF);	// take LSB only. So get bytes value 0x00 - 0xFF
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
    	// Выбор карты и настройка режима работы POLLING MODE
    	SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
    	SD_SetDeviceMode(SD_POLLING_MODE);
    	
		printf("----- SD-card Block %d bytes writing! ---- \n", BUFFER_SIZE_BYTES);
    	// запись блока данных
		disk_write(0, writeBuffer_bytes, START_SECTOR_NUM, SECTORS_QUANTITY); 
		
		
		printf("----- SD-card Block %d bytes reading! ---- \n", BUFFER_SIZE_BYTES);
		// чтение блока данных
		disk_read(0, readData_8, 65544, 4);

		
		if(SD_ErrorState == SD_OK) usart1_send(readData_8, BUFFER_SIZE_BYTES);
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

	