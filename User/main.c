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
#include "w5500_conf.h"
#include "ping.h"
#include "dhcp.h"
#include "tcp_demo.h"
#include "udp_demo.h"


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

    gpio_for_w5500_config();                                /*��ʼ��MCU�������*/
    printf("\r\n w5500_ok \r\n");
    reset_w5500();                                          /*Ӳ��λW5500*/
    printf("\r\n Reset_w5500_ok \r\n");
    set_w5500_mac();                                        /*����MAC��ַ*/
    //ip_from = IP_FROM_DEFINE;
    //set_w5500_ip();                                         /*����IP��ַ*/
    //printf("\r\n Network_ok \r\n");
    socket_buf_init(txsize, rxsize);        /*��ʼ��8��Socket�ķ��ͽ��ջ����С*/
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
