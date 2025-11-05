#pragma once
#include <stdint.h>
#include <stdbool.h>

/* 按键事件类型 (工业常用事件集合) */
typedef enum {
    KEY_EVENT_SHORT_PRESS,    // 短按
    KEY_EVENT_DOUBLE_CLICK,   // 双击
    KEY_EVENT_LONG_PRESS,     // 长按
    KEY_EVENT_CONTINUOUS      // 连发
} Key_Event;

// 消抖参数配置
#define DEBOUNCE_TICKS     3   // 消抖所需稳定次数 (3 * 10ms=30ms)
#define SCAN_INTERVAL_MS   10  // 严格保持10ms扫描周期
#define LONG_PRESS_MS       1500    // 长按时间阈值
#define DOUBLE_CLICK_MS     300     // 双击间隔阈值
#define CONTINUOUS_INIT_MS   300   // 长按后首次连发延迟
#define CONTINUOUS_INTV_MS   200   // 连发间隔时间
/* 按键状态机 */
typedef struct {
    /* 核心状态 */
    uint8_t  id;                 // 按键ID
    bool     is_pressed;         // 当前物理按下状态
    bool     stable_state;       // 消抖后稳定状态
    
    /* 时间记录 */
    uint32_t press_tick;         // 按下时刻
    uint32_t release_tick;       // 释放时刻
    uint32_t last_release_tick;  // 用于双击检测
    
    /* 事件控制 */
    bool     pending_short;      // 短按待处理
    uint8_t  click_count;        // 连击计数
    bool     is_long_trig;       // 长按已触发
    
    /* 连发控制 */
    uint32_t cont_start_tick;    // 连发开始时刻
    uint16_t cont_count;         // 连发次数
    
    /* 消抖控制 */
    uint8_t  debounce_cnt;       // 消抖计数器
} Key_State;

/* 回调函数原型 */
typedef void (*Key_Event_Callback)(uint8_t key_id, Key_Event event);

/* 核心API */
void Key_Scan_Task(uint32_t now_tick);
void Key_RegisterCallback(uint8_t key_id, Key_Event_Callback cb);
