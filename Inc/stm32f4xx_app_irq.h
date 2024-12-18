#ifndef __STM32F4XX_APP_IRQ_H__
#define __STM32F4XX_APP_IRQ_H__

//#include "stm32f4xx_hal_spi.h"
void nvic_irq_init(void);

/* Port IRQ CALL BACKS */
void Port_EXT0_IRQ_CB(void);
void Port_EXTI15_10_IRQ_CB(void);

/* Spi IRQ CALL ACKS */
void Spi_SPI1_IRQ_TX_CB(SpiEventType event);

#endif /* __STM32F4XX_APP_IRQ_H__ */
