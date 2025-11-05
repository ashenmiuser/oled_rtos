#include "bsp_key_port.h"
#include "bsp_key_driver.h"
/* 硬件配置表 (根据实际电路修改) */
static const Key_HW_Config key_hw[KEY_NUM_MAX] = {
    {GPIOD, GPIO_PIN_3 , GPIO_PIN_RESET},  // KEY0 低电平有效
    {GPIOD, GPIO_PIN_4 , GPIO_PIN_RESET},   // KEY1 高电平有效
    {GPIOD, GPIO_PIN_5 , GPIO_PIN_RESET},   // KEY2
    {GPIOE, GPIO_PIN_13, GPIO_PIN_RESET}   // KEY3
};

void Key_HW_Init(void) {
    // 由CubeMX生成的GPIO初始化代码
    GPIO_InitTypeDef gpio_init_struct;                          /*GPIO配置参数存储变量*/
    __HAL_RCC_GPIOB_CLK_ENABLE();                                     /* KEY0时钟使能 */
    __HAL_RCC_GPIOE_CLK_ENABLE();                                     /* KEY1时钟使能 */

    gpio_init_struct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;                       /* KEY0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(GPIOD, &gpio_init_struct);           /* KEY0引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = GPIO_PIN_13;                       /* KEY1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(GPIOE, &gpio_init_struct);           /* KEY1引脚模式设置,上拉输入 */


}

bool Key_ReadPin(uint8_t key_id) {
    if(key_id >= KEY_NUM_MAX) return false;
    GPIO_PinState state = HAL_GPIO_ReadPin(key_hw[key_id].port, key_hw[key_id].pin);
    return (state == key_hw[key_id].active);
}

/* 回调函数实现 */
void Key1_Handler(uint8_t key_id, Key_Event event) {
    switch(event) {
        case KEY_EVENT_SHORT_PRESS:
           printf("key1 short press\r\n");
            break;
        case KEY_EVENT_LONG_PRESS:
            printf("key1 long press\r\n");
            break;
        case KEY_EVENT_DOUBLE_CLICK:
            printf("key1 double click\r\n");
            break;
        case KEY_EVENT_CONTINUOUS:
            printf("key1 continuous press\r\n");
            break;
    }
}
