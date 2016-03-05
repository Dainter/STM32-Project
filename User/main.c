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
#include "bsp_SysTick.h"
#include "bsp_led.h"
#include "bsp_usart1.h"
#include "bsp_spi_flash.h"
#include "ff.h"

FIL fnew;								/* file objects */
FATFS fs;								/* Work area (file system object) for logical drives */
FRESULT res_flash; 
UINT br, bw;            					/* File R/W count */
uint8_t Tx_Buffer[] = "Dainter von Preussen, King of Preusia, Emporer of the Deutschland Reich.";
uint8_t Rx_Buffer[1024]={0};       		  /* file copy buffer */


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

	/* ����SysTick Ϊ10us�ж�һ�� */
	SysTick_Init();
		/* USART1 ����ģʽΪ 115200 8-N-1���жϽ��� */
	USARTx_Config();
	printf("\r\n usart_ok \r\n");	


    for(;;)
	{

		LED2_TOGGLE;
		Delay_ms(500);

	}     
	
}
/*********************************************END OF FILE**********************/
