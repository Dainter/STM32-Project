/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   systick系统定时器
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
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
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
    uint32_t flash_id;
	/* LED 端口初始化 */
	LED_GPIO_Config();

	/* 配置SysTick 为10us中断一次 */
	SysTick_Init();
		/* USART1 配置模式为 115200 8-N-1，中断接收 */
	USARTx_Config();
	printf("\r\n 这是一个串口中断接收回显实验 \r\n");	
	printf("\r\n 请在超级终端或者串口调试助手输入字符 \r\n");	
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
