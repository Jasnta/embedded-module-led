#include "bsp_led.h"

/*! ********************************************************
* @name    bsp_led_init
* @desc    LED初始化
* *********************************************************/
void bsp_led_init(void)
{
    gpio_init_type gpio_init_struct;
    gpio_default_para_init(&gpio_init_struct);
    
    /* 使能时钟 */
    crm_periph_clock_enable(CRM_GPIOF_PERIPH_CLOCK, TRUE);
    
    /* 设置默认输出电平 */
    gpio_bits_write(LED_GREEN_GPIO, LED_GREEN_GPIO_PIN, (confirm_state)(!(LED_GREEN_ON_LEVEL)));
    gpio_bits_write(LED_RED_GPIO, LED_RED_GPIO_PIN, (confirm_state)(!(LED_RED_ON_LEVEL)));
    
    /* 配置推挽输出 */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = LED_GREEN_GPIO_PIN | LED_RED_GPIO_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOF, &gpio_init_struct);
}

/*! ********************************************************
* @name    bsp_led_on
* @desc    打开LED
* @param   led：LED索引（bsp_led_t）
* *********************************************************/
void bsp_led_on(bsp_led_t led)
{
    switch(led)
    {
        case BSP_LED_GREEN:
            gpio_bits_write(LED_GREEN_GPIO, LED_GREEN_GPIO_PIN, (confirm_state)(LED_GREEN_ON_LEVEL));
            break;
        
        case BSP_LED_RED:
            gpio_bits_write(LED_RED_GPIO, LED_RED_GPIO_PIN, (confirm_state)(LED_RED_ON_LEVEL));
            break;
        
        case BSP_LED_ALL:
            gpio_bits_write(LED_GREEN_GPIO, LED_GREEN_GPIO_PIN, (confirm_state)(LED_GREEN_ON_LEVEL));
            gpio_bits_write(LED_RED_GPIO, LED_RED_GPIO_PIN, (confirm_state)(LED_RED_ON_LEVEL));
            break;
        
        default:
            break;
    }
}

/*! ********************************************************
* @name    bsp_led_off
* @desc    关闭LED
* @param   led：LED索引（bsp_led_t）
* *********************************************************/
void bsp_led_off(bsp_led_t led)
{
    switch(led)
    {
        case BSP_LED_GREEN:
            gpio_bits_write(LED_GREEN_GPIO, LED_GREEN_GPIO_PIN, (confirm_state)(!(LED_GREEN_ON_LEVEL)));
            break;
        
        case BSP_LED_RED:
            gpio_bits_write(LED_RED_GPIO, LED_RED_GPIO_PIN, (confirm_state)(!(LED_RED_ON_LEVEL)));
            break;
        
        case BSP_LED_ALL:
            gpio_bits_write(LED_GREEN_GPIO, LED_GREEN_GPIO_PIN, (confirm_state)(!(LED_GREEN_ON_LEVEL)));
            gpio_bits_write(LED_RED_GPIO, LED_RED_GPIO_PIN, (confirm_state)(!(LED_RED_ON_LEVEL)));
            break;
        
        default:
            break;
    }
}

/*! ********************************************************
* @name    bsp_led_toggle
* @desc    翻转LED
* @param   led：LED索引（bsp_led_t）
* *********************************************************/
void bsp_led_toggle(bsp_led_t led)
{
    switch(led)
    {
        case BSP_LED_GREEN:
            gpio_bits_toggle(LED_GREEN_GPIO, LED_GREEN_GPIO_PIN);
            break;
        
        case BSP_LED_RED:
            gpio_bits_toggle(LED_RED_GPIO, LED_RED_GPIO_PIN);
            break;
        
        case BSP_LED_ALL:
            gpio_bits_toggle(LED_GREEN_GPIO, LED_GREEN_GPIO_PIN);
            gpio_bits_toggle(LED_RED_GPIO, LED_RED_GPIO_PIN);
            break;
        
        default:
            break;
    }
}
