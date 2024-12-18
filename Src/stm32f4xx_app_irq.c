#include "stm32xxxx.h"
#include "stm32f4xx_hal_port.h"
#include "stm32f4xx_hal_spi.h"
#include "app_gpio.h"
#include "stm32f4xx_app_irq.h"

void nvic_irq_init(void)
{
    NVIC_EnableIRQ(EXTI15_10_IRQn); /* GPIO PIN 10 to 15 Interrupt Enable */
    NVIC_EnableIRQ(SPI1_IRQn); 
}

void nvic_irq_deinit(void)
{
    NVIC_DisableIRQ(EXTI15_10_IRQn); /* GPIO PIN 10 to 15 Interrupt Enable */
    NVIC_DisableIRQ(SPI1_IRQn); 
}

void EXTI0_IRQHandler(void)
{
    /* Debounce time for Button Press */
    for(int i=0; i<50000; i++);
    Port_EXTI0_IRQHandler(PORT_PIN_11);
}

void EXTI15_10_IRQHandler(void)
{
  Port_EXTI15_10_IRQHandler(PUSH_BUTTON_PIN);
}

void SPI1_IRQHandler(void)
{
    // Spi_SPI1_IRQHandler();
}

void Port_EXT0_IRQ_CB(void)
{
    /* Interrupt Code */
}

void Port_EXTI15_10_IRQ_CB(void)
{
    /* Interrupt Code */
    Port_TogglePin(LED_PORT, LED_PIN);
}

void Spi_SPI1_IRQ_TX_CB(SpiEventType event)
{
    /* User Code */
    
}

void Spi_SPI1_IRQ_RX_CB(void)
{
    /* SPI1 Receive Code */
}
