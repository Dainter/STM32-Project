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

    while(1)
    {
        LED2_TOGGLE;
        SysTick_Delay_ms(500);
    }     
    
}

/*********************************************END OF FILE**********************/
