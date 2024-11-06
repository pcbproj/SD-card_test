/*******************************************************************/
#include "main.h"



/*******************************************************************/
#define BUFFER_SIZE	8

uint32_t writeBuffer[BUFFER_SIZE]; 
uint32_t readBuffer[BUFFER_SIZE];


SD_CardInfo SDCardInfo;



/*******************************************************************/
int main()
{
	RCC_Init();
	APP_GPIO_Init();
	USART1_Init();		// for debug baudrate = 115200


	// Тестовые данные для записи
    for (uint16_t i = 0; i < 512; i++)
    {
        writeBuffer[i] = i % 256;
        readBuffer[i] = 0;
    }

	printf("---- System started! ---- \n");

	printf("----- SD-card initialization started! ---- \n");
    // Иницилизация карты
	SD_Init();
	
	printf("----- SD-card Getting information! ---- \n");
    // Получаем информацию о карте
    SD_GetCardInfo(&SDCardInfo);
    
	printf("----- SD-card Selecting! ---- \n");
    // Выбор карты и настройка режима работы
    SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
    SD_SetDeviceMode(SD_POLLING_MODE);
    
	printf("----- SD-card Block 512 bytes writing! ---- \n");
    // И вот наконец-то запись и чтение
    SD_WriteBlock(0x00000000, writeBuffer, 512);

	printf("----- SD-card Block 512 bytes reading! ---- \n");
    SD_ReadBlock(0x00000000, readBuffer, 512);
	
	usart1_send_w32(readBuffer, BUFFER_SIZE);

	
	while(1)
	{
	}
}



/*******************************************************************/

	