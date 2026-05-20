#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "config.h"

/* LED索引 */
typedef enum {
    BSP_LED_GREEN = 0,
    BSP_LED_RED,
    
    BSP_LED_COUNT,
    BSP_LED_ALL,
} bsp_led_t;

/* ************************************************************************
*  LED板级硬件驱动接口
*  ************************************************************************ */
void bsp_led_init(void);
void bsp_led_on(bsp_led_t led);
void bsp_led_off(bsp_led_t led);
void bsp_led_toggle(bsp_led_t led);

#endif
