/**
 ****************************************************************************************************
 * @file        delay.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-17
 * @brief       使用SysTick的普通计数模式对延迟进行管理(支持ucosii)
 *              提供delay_init初始化函数， delay_us和delay_ms等延时函数
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20200417
 * 第一次发布
 * V1.0 20200523
 * 增加 HAL_Delay 函数，用于Hal库内部函数的延时退出
 *
 ****************************************************************************************************
 */
 
#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f1xx.h"
#include "stdint.h"
/* 获取内核时钟频率 */
#define GET_CPU_ClkFreq()       HAL_RCC_GetSysClockFreq()
#define SysClockFreq            (72000000)
/* 为方便使用，在延时函数内部调用CPU_TS_TmrInit函数初始化时间戳寄存器，
   这样每次调用函数都会初始化一遍。
   把本宏值设置为0，然后在main函数刚运行时调用CPU_TS_TmrInit可避免每次都初始化 */  

#define CPU_TS_INIT_IN_DELAY_FUNCTION   0  
// void delay_init(uint16_t sysclk);       /* 初始化延迟函数 */
HAL_StatusTypeDef HAL_Delay_Init(void);
void delay_ms(uint16_t nms);            /* 延时nms */
void delay_us(uint32_t nus);            /* 延时nus */

#if (!SYS_SUPPORT_OS)                   /* 没有使用Systick中断 */
    void HAL_Delay(uint32_t Delay);     /* HAL库的延时函数，SDIO等需要用到 */
#endif

#endif





























