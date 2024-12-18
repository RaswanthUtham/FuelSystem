#include "stm32xxxx.h"
#include "stm32f4xx_hal_port.h"
#include "app_gpio.h"

static Port_ConfigType LedPortConfig;
static Port_ConfigType PushButtonPortConfig;

void led_port_init(void)
{
    LedPortConfig.Port = LED_PORT;
    LedPortConfig.Pin = LED_PIN;
    LedPortConfig.Mode = PORT_PIN_MODE_OUTPUT_PP;
    LedPortConfig.Speed = PORT_PIN_SPEED_FREQ_HIGH;
    LedPortConfig.Pull = PORT_PIN_NOPULL;
    Port_Init(&LedPortConfig);
}

void toggle_led(void)
{
  Port_TogglePin(LedPortConfig.Port, LED_PIN);
}

void push_button_port_init(void)
{
    PushButtonPortConfig.Port = PUSH_BUTTON_PORT;
    PushButtonPortConfig.Pin = PUSH_BUTTON_PIN;
    PushButtonPortConfig.Mode = PORT_PIN_MODE_IT_FALLING;
    PushButtonPortConfig.Speed = PORT_PIN_SPEED_FREQ_HIGH;
    PushButtonPortConfig.Pull = PORT_PIN_PULLUP;
    Port_Init(&PushButtonPortConfig);
}



