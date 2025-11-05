#pragma once
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "bsp_key_driver.h"
#include "usart.h"
#define KEY_NUM_MAX 4
/* 硬件按键配置表 */
typedef struct {
    GPIO_TypeDef* port;     // GPIO端口
    uint16_t pin;           // 引脚号
    GPIO_PinState active;   // 有效电平 (GPIO_PIN_SET/GPIO_PIN_RESET)
} Key_HW_Config;

/* 硬件相关接口 */
void Key_HW_Init(void);
bool Key_ReadPin(uint8_t key_id);
void Key1_Handler(uint8_t key_id, Key_Event event);

