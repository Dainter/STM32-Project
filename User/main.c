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

// ����Ա

/*
 * t : ��ʱʱ�� 
 * Ticks : ���ٸ�ʱ�����ڲ���һ���ж� 
 * f : ʱ��Ƶ�� 72000000
 * t = Ticks * 1/f = (72000000/100000) * (1/72000000) = 10us 
 */ 

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
	printf("\r\n ����һ�������жϽ��ջ���ʵ�� \r\n");	
	printf("\r\n ���ڳ����ն˻��ߴ��ڵ������������ַ� \r\n");	
  
	for(;;)
	{

		LED1( ON ); 
		Delay_ms(500);
		LED1( OFF );

		LED2( ON );
		Delay_ms(500);
		LED2( OFF );

		LED3( ON );
		Delay_ms(500);
		LED3( OFF );	

	}     
	
}
/*********************************************END OF FILE**********************/
