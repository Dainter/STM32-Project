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
#include "bsp_SysTick.h"
#include "bsp_led.h"
#include "bsp_usart1.h"



/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{   
    /* LED 端口初始化 */
    LED_GPIO_Config();

    /* 配置SysTick 为10us中断一次 */
    SysTick_Init();
    /* USART1 配置模式为 115200 8-N-1，中断接收 */
    USARTx_Config();
    printf("\r\n usart_ok \r\n");   

    while(1)
    {
        LED2_TOGGLE;
        SysTick_Delay_ms(500);
    }     
    
}

/*********************************************END OF FILE**********************/
