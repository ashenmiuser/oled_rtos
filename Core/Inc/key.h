#ifndef __KEY_H
#define __KEY_H

#include "stm32f1xx_hal.h" 
#include "stdint.h"
#include "delay.h"
#define KEY1_GPIO_PORT                  GPIOB 
#define KEY1_GPIO_PIN                   GPIO_PIN_0
#define KEY1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define KEY2_GPIO_PORT                  GPIOB
#define KEY2_GPIO_PIN                   GPIO_PIN_1
#define KEY2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define KEY3_GPIO_PORT                  GPIOB
#define KEY3_GPIO_PIN                   GPIO_PIN_10
#define KEY3_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define KEY4_GPIO_PORT                  GPIOB
#define KEY4_GPIO_PIN                   GPIO_PIN_11
#define KEY4_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */


#define KEY1        HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN)     /* 读取KEY0引脚 */
#define KEY2        HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY2_GPIO_PIN)     /* 读取KEY1引脚 */
#define KEY3        HAL_GPIO_ReadPin(KEY3_GPIO_PORT, KEY3_GPIO_PIN)     /* 读取KEY2引脚 */
#define KEY4        HAL_GPIO_ReadPin(KEY4_GPIO_PORT, KEY4_GPIO_PIN)     /* 读取WKUP引脚 */


#define KEY1_PRES    1              /* KEY0按下 */
#define KEY2_PRES    2              /* KEY1按下 */
#define KEY3_PRES    3              /* KEY2按下 */
#define KEY4_PRES    4              /* KEY_UP按下(即WK_UP) */

void key_init(void);                /* 按键初始化函数 */
uint8_t key_scan(uint8_t mode);     /* 按键扫描函数 */

#endif
