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
#include "bsp_spi_flash.h"
#include "ff.h"
#include "w5500_conf.h"
#include "ping.h"
#include "dhcp.h"
#include "tcp_demo.h"
#include "udp_demo.h"


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

    gpio_for_w5500_config();                                /*初始化MCU相关引脚*/
    printf("\r\n w5500_ok \r\n");
    reset_w5500();                                          /*硬复位W5500*/
    printf("\r\n Reset_w5500_ok \r\n");
    set_w5500_mac();                                        /*配置MAC地址*/
    //ip_from = IP_FROM_DEFINE;
    //set_w5500_ip();                                         /*配置IP地址*/
    //printf("\r\n Network_ok \r\n");
    socket_buf_init(txsize, rxsize);        /*初始化8个Socket的发送接收缓存大小*/
    printf("\r\n Socket_ok \r\n");
    while(dhcp_ok != 1)
    {
        do_dhcp();
    }
    do_ping();
    printf("\r\n Ping Test \r\n");
    while(1)
    {
        ping_listening();
        //do_tcp_server();
        do_udp();
        LED2_TOGGLE;
        SysTick_Delay_ms(500);

    }     
    
}
/*********************************************END OF FILE**********************/
