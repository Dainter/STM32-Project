/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : EHS
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
OS_SEM  print_flag;

/*
*********************************************************************************************************
*                                                 TCB
*********************************************************************************************************
*/

static  OS_TCB   AppTaskStartTCB;
static  OS_TCB   AppTaskLED1TCB;
static  OS_TCB   AppTaskLED2TCB;
static  OS_TCB   AppTaskLED3TCB;

/*
*********************************************************************************************************
*                                                STACKS
*********************************************************************************************************
*/

static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];
static  CPU_STK  AppTaskLED1Stk[APP_TASK_LED1_STK_SIZE];
static  CPU_STK  AppTaskLED2Stk[APP_TASK_LED2_STK_SIZE];
static  CPU_STK  AppTaskLED3Stk[APP_TASK_LED3_STK_SIZE];

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart  (void *p_arg);
static  void  AppTaskLED1  (void *p_arg);
static  void  AppTaskLED2  (void *p_arg);
static  void  AppTaskLED3  (void *p_arg);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int  main (void)
{
    OS_ERR  err;


    OSInit(&err);                                               /* Init uC/OS-III.                                      */
    
    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task Start",
                 (OS_TASK_PTR ) AppTaskStart,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_START_PRIO,
                 (CPU_STK    *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    OS_ERR      err;


   (void)p_arg;

    BSP_Init();                                                 /* Initialize BSP functions                             */
    CPU_Init();

    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
    cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        /* Determine nbr SysTick increments                     */
    OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */

    Mem_Init();                                                 /* Initialize Memory Management Module                  */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

    CPU_IntDisMeasMaxCurReset();
    printf("App Task LED1 Create.\n");
    OSTaskCreate((OS_TCB     *)&AppTaskLED1TCB,                /* Create the LED1 task                                */
             (CPU_CHAR   *)"App Task LED1",
             (OS_TASK_PTR ) AppTaskLED1,
             (void       *) 0,
             (OS_PRIO     ) APP_TASK_LED1_PRIO,
             (CPU_STK    *)&AppTaskLED1Stk[0],
             (CPU_STK_SIZE) APP_TASK_LED1_STK_SIZE / 10,
             (CPU_STK_SIZE) APP_TASK_LED1_STK_SIZE,
             (OS_MSG_QTY  ) 5u,
             (OS_TICK     ) 0u,
             (void       *) 0,
             (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
             (OS_ERR     *)&err);
    
    printf("App Task LED2 Create.\n");         
    OSTaskCreate((OS_TCB     *)&AppTaskLED2TCB,                /* Create the LED2 task                                */
             (CPU_CHAR   *)"App Task LED2",
             (OS_TASK_PTR ) AppTaskLED2,
             (void       *) 0,
             (OS_PRIO     ) APP_TASK_LED2_PRIO,
             (CPU_STK    *)&AppTaskLED2Stk[0],
             (CPU_STK_SIZE) APP_TASK_LED2_STK_SIZE / 10,
             (CPU_STK_SIZE) APP_TASK_LED2_STK_SIZE,
             (OS_MSG_QTY  ) 5u,
             (OS_TICK     ) 0u,
             (void       *) 0,
             (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
             (OS_ERR     *)&err);
             
    printf("App Task LED3 Create.\n");
    OSTaskCreate((OS_TCB     *)&AppTaskLED3TCB,                /* Create the LED3 task                                */
             (CPU_CHAR   *)"App Task LED3",
             (OS_TASK_PTR ) AppTaskLED3,
             (void       *) 0,
             (OS_PRIO     ) APP_TASK_LED3_PRIO,
             (CPU_STK    *)&AppTaskLED3Stk[0],
             (CPU_STK_SIZE) APP_TASK_LED3_STK_SIZE / 10,
             (CPU_STK_SIZE) APP_TASK_LED3_STK_SIZE,
             (OS_MSG_QTY  ) 5u,
             (OS_TICK     ) 0u,
             (void       *) 0,
             (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
             (OS_ERR     *)&err);

    OSSemCreate ((OS_SEM      *)&print_flag,
                (CPU_CHAR    *)"print_flag",
                (OS_SEM_CTR   )2,
                (OS_ERR     *)&err);


             
    OSTaskDel((OS_TCB     *)&AppTaskStartTCB,
             (OS_ERR     *)&err);
    printf("App Task Start Delete.\n");
}
/*
*********************************************************************************************************
*                                          LED1 TASK
*
* Description : 
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 
*********************************************************************************************************
*/

static  void  AppTaskLED1 (void *p_arg)
{
    OS_ERR      err;
    OS_SEM_CTR  ctr;
		CPU_SR_ALLOC();

   (void)p_arg;


    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        OS_CRITICAL_ENTER();
        printf("LED1 Wait for SEM.\n");
        OS_CRITICAL_EXIT(); 
        ctr = OSSemPend ((OS_SEM   *)&print_flag,               //等待该信号量 SemOfKey
                        (OS_TICK   )0,                       //下面选择不等待，该参无效
                        (OS_OPT    )OS_OPT_PEND_BLOCKING,//如果没信号量可用不等待
                        (CPU_TS   *)0,                       //不获取时间戳
                        (OS_ERR   *)&err);                   //返回错误类型
        OS_CRITICAL_ENTER();
        if(err == OS_ERR_NONE)
        {
            printf("LED1 Get SEM. SEM ctr = %d\n", ctr);
        }
        else
        {
            printf("LED1 dosen't Get SEM. err = %d\n", err);
        }
        OS_CRITICAL_EXIT();
        LED1_TOGGLE;

        ctr = OSSemPost ((OS_SEM  *)&print_flag,
                        (OS_OPT   )OS_OPT_POST_ALL,
                        (OS_ERR     *)&err);
        OS_CRITICAL_ENTER();
        if(err == OS_ERR_NONE)
        {
            printf("LED1 Post SEM. SEM ctr = %d\n", ctr);
        }
        else
        {
            printf("LED1 dosen't Post SEM. err = %d\n", err);
        }
        OS_CRITICAL_EXIT();
        OSTimeDly(500,
                  OS_OPT_TIME_DLY,
                  &err);
                  
    }
}

/*
*********************************************************************************************************
*                                          LED2 TASK
*
* Description : 
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 
*********************************************************************************************************
*/

static  void  AppTaskLED2 (void *p_arg)
{
    OS_ERR      err;
    OS_SEM_CTR  ctr;
		CPU_SR_ALLOC();

   (void)p_arg;


    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        OS_CRITICAL_ENTER();
				printf("LED2 Wait for SEM.\n");
				OS_CRITICAL_EXIT();
        ctr = OSSemPend ((OS_SEM   *)&print_flag,               //等待该信号量 SemOfKey
                        (OS_TICK   )0,                       //下面选择不等待，该参无效
                        (OS_OPT    )OS_OPT_PEND_BLOCKING,//如果没信号量可用不等待
                        (CPU_TS   *)0,                       //不获取时间戳
                        (OS_ERR   *)&err);                   //返回错误类型
				OS_CRITICAL_ENTER();
        if(err == OS_ERR_NONE)
        {
            printf("LED2 Get SEM. SEM ctr = %d\n", ctr);
        }
        else
        {
            printf("LED2 dosen't Get SEM. err = %d\n", err);
        }
				OS_CRITICAL_EXIT();
        LED2_TOGGLE;

        ctr = OSSemPost ((OS_SEM  *)&print_flag,
                        (OS_OPT   )OS_OPT_POST_ALL,
                        (OS_ERR     *)&err);
				OS_CRITICAL_ENTER();
        if(err == OS_ERR_NONE)
        {
            printf("LED2 Post SEM. SEM ctr = %d\n", ctr);
        }
        else
        {
            printf("LED2 dosen't Post SEM. err = %d\n", err);
        }
				OS_CRITICAL_EXIT();
        OSTimeDly(1000,
                  OS_OPT_TIME_DLY,
                  &err);
    }
}

/*
*********************************************************************************************************
*                                          LED3 TASK
*
* Description : 
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 
*********************************************************************************************************
*/

static  void  AppTaskLED3 (void *p_arg)
{
    OS_ERR      err;
    OS_SEM_CTR  ctr;
		CPU_SR_ALLOC();

   (void)p_arg;


    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        OS_CRITICAL_ENTER();
				printf("LED3 Wait for SEM.\n");
				OS_CRITICAL_EXIT();
        ctr = OSSemPend ((OS_SEM   *)&print_flag,               //等待该信号量 SemOfKey
                        (OS_TICK   )0,                       //下面选择不等待，该参无效
                        (OS_OPT    )OS_OPT_PEND_BLOCKING,//如果没信号量可用不等待
                        (CPU_TS   *)0,                       //不获取时间戳
                        (OS_ERR   *)&err);                   //返回错误类型
        OS_CRITICAL_ENTER();
				if(err == OS_ERR_NONE)
        {
            printf("LED3 Get SEM. SEM ctr = %d\n", ctr);
        }
        else
        {
            printf("LED3 dosen't Get SEM. err = %d\n", err);
        }
				OS_CRITICAL_EXIT();
        LED3_TOGGLE;

        ctr = OSSemPost ((OS_SEM  *)&print_flag,
                        (OS_OPT   )OS_OPT_POST_ALL,
                        (OS_ERR     *)&err);
				OS_CRITICAL_ENTER();
        if(err == OS_ERR_NONE)
        {
            printf("LED3 Post SEM. SEM ctr = %d\n", ctr);
        }
        else
        {
            printf("LED3 dosen't Post SEM. err = %d\n", err);
        }
				OS_CRITICAL_EXIT();
        OSTimeDly(2000,
                  OS_OPT_TIME_DLY,
                  &err);
    }
}
