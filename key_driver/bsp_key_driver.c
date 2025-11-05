#include "bsp_key_driver.h"
#include "bsp_key_port.h"



static Key_State keys[KEY_NUM_MAX] = {0};
static Key_Event_Callback callbacks[KEY_NUM_MAX] = {NULL};

void Key_RegisterCallback(uint8_t key_id, Key_Event_Callback cb) {
    if(key_id < KEY_NUM_MAX) callbacks[key_id] = cb;
}
// 事件触发统一接口
static void TriggerEvent(uint8_t key_id, Key_Event event) {
    if(callbacks[key_id]) {
        callbacks[key_id](key_id, event);
    }
}

void Key_Scan_Task(uint32_t now_tick) {
    static uint32_t last_scan = 0;
    if(now_tick - last_scan < SCAN_INTERVAL_MS) return;
    last_scan = now_tick;

    for(uint8_t i = 0; i < KEY_NUM_MAX; i++) {
        Key_State* key = &keys[i];
        bool raw_state = Key_ReadPin(i);

        /* 消抖处理（增强稳定性） */
        if(raw_state != key->stable_state) {
            if(++key->debounce_cnt >= DEBOUNCE_TICKS) {
                key->stable_state = raw_state;
                key->debounce_cnt = 0;
            }
        } else {
            key->debounce_cnt = 0;
        }

        /* 状态迁移检测 */
        if(key->is_pressed != key->stable_state) {
            key->is_pressed = key->stable_state;
            
            if(key->is_pressed) { // 按下事件
                key->press_tick = now_tick;
                key->is_long_trig = false;
                
                // 双击检测
                if((now_tick - key->last_release_tick) < DOUBLE_CLICK_MS) {
                    key->click_count = (key->click_count < 2) ? key->click_count + 1 : 2;
                } else {
                    key->click_count = 1;
                }
            } else { // 释放事件
                key->release_tick = now_tick;
                key->last_release_tick = now_tick;
                
                // 短按待处理标记
                if((now_tick - key->press_tick) < LONG_PRESS_MS) {
                    key->pending_short = true;
                }
                
                // 重置连发状态
                key->cont_count = 0;
                key->cont_start_tick = 0;
            }
        }

        /* 事件处理流水线 */
        // 双击超时处理
        if(!key->is_pressed && key->pending_short) {
            if((now_tick - key->release_tick) >= DOUBLE_CLICK_MS) {
                if(key->click_count >= 2) {
                    TriggerEvent(i, KEY_EVENT_DOUBLE_CLICK);
                } else {
                    TriggerEvent(i, KEY_EVENT_SHORT_PRESS);
                }
                key->pending_short = false;
                key->click_count = 0;
            }
        }

        // 长按检测（互斥锁设计）
        if(key->is_pressed && !key->is_long_trig) {
            if((now_tick - key->press_tick) >= LONG_PRESS_MS) {
                key->is_long_trig = true;
                key->pending_short = false;
                key->click_count = 0;
                
                // 初始化连发参数
                key->cont_start_tick = now_tick + CONTINUOUS_INIT_MS; // 延迟启动
                key->cont_count = 0;
                
                TriggerEvent(i, KEY_EVENT_LONG_PRESS);
            }
        }

        // 连发检测（精准时间锚点）
        if(key->is_pressed && key->is_long_trig) {
            if(now_tick >= key->cont_start_tick) {
                uint32_t elapsed = now_tick - key->cont_start_tick;
                uint32_t req_interval = (key->cont_count == 0) ? CONTINUOUS_INIT_MS : CONTINUOUS_INTV_MS;
                
                if(elapsed >= req_interval) {
                    TriggerEvent(i, KEY_EVENT_CONTINUOUS);
                    key->cont_start_tick = now_tick;
                    key->cont_count++;
                }
            }
        }
    }
}
