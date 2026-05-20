#include "mod_led.h"
#include <string.h>
#include "bsp_tick.h"

/* LED控制结构体 */
typedef struct {
    uint16_t blink_interval;  // 闪烁间隔
    uint16_t blink_duration;  // 闪烁总时长
    uint16_t tick_flash;      // 翻转计时
    uint16_t tick_start;      // 开始计时
    uint8_t  mode;            // 模式
    
} mod_led_ctrl_t;

static mod_led_ctrl_t s_mod_led_ctrl[BSP_LED_COUNT] = {0};

/*! ********************************************************
* @name    mod_led_init
* @desc    初始化LED组件
* *********************************************************/
void mod_led_init(void)
{
    memset(s_mod_led_ctrl, 0, sizeof(s_mod_led_ctrl));
    bsp_led_off(BSP_LED_ALL);
}

/*! ********************************************************
* @name    mod_led_set
* @desc    设置LED模式
* @param   led：LED索引（bsp_led_t）
*          mode：LED模式（mod_led_mode_t）
*          blink_interval：闪烁间隔（ms）
*          blink_duration：闪烁总时长（ms）
* *********************************************************/
void mod_led_set(bsp_led_t led, mod_led_mode_t mode, uint16_t blink_interval, uint16_t blink_duration)
{
    if(led>=BSP_LED_COUNT) return;
    
    s_mod_led_ctrl[led].mode = mode;
    
    switch(mode)
    {
        case MOD_LED_MODE_ON:   bsp_led_on(led);  break;
        
        case MOD_LED_MODE_OFF:  bsp_led_off(led); break;
        
        case MOD_LED_MODE_BLINK:
        {
            s_mod_led_ctrl[led].blink_interval = blink_interval;
            s_mod_led_ctrl[led].blink_duration = blink_duration;
        
            /* 记录当前系统时间 */
            uint16_t cur_tick = bsp_tick_get();
            s_mod_led_ctrl[led].tick_flash = cur_tick;
            s_mod_led_ctrl[led].tick_start = cur_tick;
        
            /* 启动闪烁→立即亮 */
            bsp_led_on(led);
            
            break;
        }
    }
}

/*! ********************************************************
* @name    mod_led_process
* @desc    LED轮询处理
* *********************************************************/
void mod_led_process(void)
{
    uint16_t cur_tick = bsp_tick_get();

    for(bsp_led_t led_idx=(bsp_led_t)0; led_idx<BSP_LED_COUNT; led_idx++)
    {
        if(s_mod_led_ctrl[led_idx].mode != MOD_LED_MODE_BLINK) continue;

        /* 闪烁翻转 */
        if(cur_tick-s_mod_led_ctrl[led_idx].tick_flash >= s_mod_led_ctrl[led_idx].blink_interval)
        {
            s_mod_led_ctrl[led_idx].tick_flash = cur_tick;
            bsp_led_toggle(led_idx);
        }

        /* 持续时间到→停止并熄灭 */
        if(cur_tick-s_mod_led_ctrl[led_idx].tick_start >= s_mod_led_ctrl[led_idx].blink_duration)
        {
            s_mod_led_ctrl[led_idx].mode = MOD_LED_MODE_OFF;
            bsp_led_off(led_idx);
        }
    }
}
