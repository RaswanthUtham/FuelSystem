#ifndef __APP_GPIO_H__
#define __APP_GPIO_H__

/* LED Toggle MACROS */
#define LED_PIN                                         STM32F446RE_USER_LED_PIN
#define LED_PORT                                        STM32F446RE_USER_LED_PORT
#define PUSH_BUTTON_PIN                                 STM32F446RE_USER_PUSH_BUTTON_PIN
#define PUSH_BUTTON_PORT                                STM32F446RE_USER_PUSH_BUTTON_PORT

/* STM32F446RE Specific Details */
#define STM32F446RE_USER_LED_PIN                        PORT_PIN_5
#define STM32F446RE_USER_LED_PORT                       (GPIOA)
#define STM32F446RE_USER_PUSH_BUTTON_PIN                PORT_PIN_13
#define STM32F446RE_USER_PUSH_BUTTON_PORT               (GPIOC)


void led_port_init(void);
void push_button_port_init(void);
void irq_init(void);
void toggle_led(void);

#endif /* __APP_GPIO_H__ */
