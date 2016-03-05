/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   systickϵͳ��ʱ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "SysTick\bsp_SysTick.h"
#include "Led\bsp_led.h"
#include "usart\bsp_usart1.h"
#include "spi_flash\bsp_spi_flash.h"


#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress

     

uint8_t Tx_Buffer[] = "Dainter von Preussen, King of Preusia, Emporer of the Deutschland Reich.";
uint8_t Rx_Buffer[BufferSize];


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
    uint32_t flash_id;
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

	/* ����SysTick Ϊ10us�ж�һ�� */
	SysTick_Init();
		/* USART1 ����ģʽΪ 115200 8-N-1���жϽ��� */
	USARTx_Config();
	printf("\r\n ����һ�������жϽ��ջ���ʵ�� \r\n");	
	printf("\r\n ���ڳ����ն˻��ߴ��ڵ������������ַ� \r\n");	
    SPI_FLASH_Init();
    
    flash_id = SPI_FLASH_ReadManufacturerID();
    printf("\r\n Manufacturer id = %d \r\n", flash_id);	
    flash_id = SPI_FLASH_ReadDeviceID();
    printf("\r\n device id = %d \r\n", flash_id);	
    
    /* Erase SPI FLASH Sector to write on */
    SPI_FLASH_SectorErase(FLASH_SectorToErase);	 	 
			
    SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
    printf("\r\n Tx_Buffer:%s \r\t", Tx_Buffer);
		

	SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
	printf("\r\n Rx_Buffer:%s \r\n", Rx_Buffer);
	for(;;)
	{

		//LED1( ON ); 
		//Delay_ms(500);
		//LED1( OFF );


	}     
	
}
/*********************************************END OF FILE**********************/
