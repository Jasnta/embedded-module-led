#ifndef __MOD_LED_H__
#define __MOD_LED_H__

#include "bsp_led.h"

/* LED模式 */
typedef enum {
    MOD_LED_MODE_OFF = 0,
    MOD_LED_MODE_ON,
    MOD_LED_MODE_BLINK,
    
} mod_led_mode_t;

/* ************************************************************************
*  LED组件逻辑接口
*  ************************************************************************ */
void mod_led_init(void);
void mod_led_set(bsp_led_t led, mod_led_mode_t mode, uint16_t blink_interval, uint16_t blink_duration);
void mod_led_process(void);

#endif
