#include "stm32xxxx.h"
#include "stm32f4xx_hal_port.h"
#include "stm32f4xx_hal_rcc.h"
#include <stddef.h>

#define PORT_LENGTH 16U

uint8_t Error_Code_Index = 0;

uint8_t Port_ClockControl(PORT_TypeDef *GPIOx, uint8_t Enable)
{
    if (!(IS_GPIO_ALL_INSTANCE(GPIOx)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_PORT;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_CLOCKCONTROL;
        Error_Code_Index++;
        return E_NOK;
    }

    uint32_t GPIO = (uint32_t)GPIOx;

    if (Enable)
    {
        switch (GPIO)
        {
        case GPIOA_BASE:
            __RCC_GPIOA_CLK_ENABLE();
            break;

        case GPIOB_BASE:
            __RCC_GPIOB_CLK_ENABLE();
            break;

        case GPIOC_BASE:
            __RCC_GPIOC_CLK_ENABLE();
            break;

        case GPIOD_BASE:
            __RCC_GPIOD_CLK_ENABLE();
            break;

        case GPIOE_BASE:
            __RCC_GPIOE_CLK_ENABLE();
            break;

        case GPIOF_BASE:
            __RCC_GPIOF_CLK_ENABLE();
            break;

        case GPIOG_BASE:
            __RCC_GPIOG_CLK_ENABLE();
            break;

        case GPIOH_BASE:
            __RCC_GPIOH_CLK_ENABLE();
            break;
        }
    }
    else
    {
        switch (GPIO)
        {
        case GPIOA_BASE:
            __RCC_GPIOA_CLK_DISABLE();
            break;

        case GPIOB_BASE:
            __RCC_GPIOB_CLK_DISABLE();
            break;

        case GPIOC_BASE:
            __RCC_GPIOC_CLK_DISABLE();
            break;

        case GPIOD_BASE:
            __RCC_GPIOD_CLK_DISABLE();
            break;

        case GPIOE_BASE:
            __RCC_GPIOE_CLK_DISABLE();
            break;

        case GPIOF_BASE:
            __RCC_GPIOF_CLK_DISABLE();
            break;

        case GPIOG_BASE:
            __RCC_GPIOG_CLK_DISABLE();
            break;

        case GPIOH_BASE:
            __RCC_GPIOH_CLK_DISABLE();
            break;
        }
    }
    return E_OK;
}

uint8_t Port_Init(const Port_ConfigType *ConfigPtr)
{
    uint32_t pin = 0;
    Port_PinType pin_pos = 0;
    Port_PinType cfg_pin_pos = 0;
    uint32_t tmp_reg = 0;
    uint8_t err = 0;

    if (!(IS_GPIO_ALL_INSTANCE(ConfigPtr->Port)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_PORT;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_INIT;
        Error_Code_Index++;
        err = 1;
    }

    if (!(IS_PORT_PIN(ConfigPtr->Pin)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_PIN;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_INIT;
        Error_Code_Index++;
        err = 2;
    }

    if (!(IS_PORT_PIN_MODE(ConfigPtr->Mode)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_MODE;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_INIT;
        Error_Code_Index++;
        err = 3;
    }

    if (err)
        return E_NOK;

    Port_ClockControl(ConfigPtr->Port, 1U); /* Enable GPIO Port Clock */

    for (pin = 0; pin < PORT_LENGTH; pin++)
    {
        pin_pos = (1U << pin);
        cfg_pin_pos = ConfigPtr->Pin & pin_pos;

        if (pin_pos == cfg_pin_pos)
        {
            if (((ConfigPtr->Mode & PORT_MODE) == MODE_OUTPUT) || ((ConfigPtr->Mode & PORT_MODE) == MODE_AF))
            {
                if (!(IS_PORT_SPEED(ConfigPtr->Speed)))
                {
                    DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_SPEED;
                    DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
                    DET_ServiceId[Error_Code_Index] = PORT_SID_INIT;
                    Error_Code_Index++;
                    err = 4;
                }
                else
                {
                    /* SPEED Config */
                    tmp_reg = ConfigPtr->Port->OSPEEDR;
                    tmp_reg &= ~(3 << (pin * 2));
                    tmp_reg |= (ConfigPtr->Speed << (pin * 2));
                    ConfigPtr->Port->OSPEEDR = tmp_reg;

                    /* Open Drain or PushPull Config */
                    tmp_reg = ConfigPtr->Port->OTYPER;
                    tmp_reg &= ~(1 << (pin * 1));
                    tmp_reg |= (((ConfigPtr->Mode & OUTPUT_TYPE) >> OUTPUT_TYPE_POS) << pin);
                    ConfigPtr->Port->OTYPER = tmp_reg;
                }
            }

            if ((ConfigPtr->Mode & PORT_MODE) == MODE_AF)
            {
                if (!(IS_PORT_AF(ConfigPtr->Alternate)))
                {
                    DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_AF;
                    DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
                    DET_ServiceId[Error_Code_Index] = PORT_SID_INIT;
                    Error_Code_Index++;
                    err = 5;
                }
                else
                {
                    /* AF Config */
                    tmp_reg = ConfigPtr->Port->AFR[pin >> 3];
                    tmp_reg &= ~(0x0F << ((uint32_t)(pin & 7ul) * 4ul));
                    tmp_reg |= (uint32_t)((uint32_t)ConfigPtr->Alternate << ((uint32_t)pin & 7ul) * 4ul);
                    ConfigPtr->Port->AFR[pin >> 3] = tmp_reg;
                }
            }

            if ((ConfigPtr->Mode & PORT_MODE) != MODE_ANALOG)
            {
                if (!(IS_PORT_PIN_PULL(ConfigPtr->Pull)))
                {
                    DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_PULL;
                    DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
                    DET_ServiceId[Error_Code_Index] = PORT_SID_INIT;
                    Error_Code_Index++;
                    err = 6;
                }
                else
                {
                    /* PullUp PullDown Config */
                    tmp_reg = ConfigPtr->Port->PUPDR;
                    tmp_reg &= ~(3 << (pin * 2));
                    tmp_reg |= (ConfigPtr->Pull << (pin * 2ul));
                    ConfigPtr->Port->PUPDR = tmp_reg;
                }
            }

            /* Mode Config (Input, Output, Analog, AF) */
            tmp_reg = ConfigPtr->Port->MODER;
            tmp_reg &= ~(3 << (pin * 2));
            tmp_reg |= (uint32_t)((ConfigPtr->Mode & PORT_MODE) << (pin * 2ul));
            ConfigPtr->Port->MODER = tmp_reg;

            /* Interrupt and Event Config */
            if ((ConfigPtr->Mode & EXTI_MODE) != 0u)
            {
                /* Enable SYSCFG Clock for Interrupts */
                __RCC_SYSCFG_CLK_ENABLE();

                /* Select the Port and Pin from which interrupt should occur */
                tmp_reg = SYSCFG->EXTICR[pin >> 2U];
                tmp_reg &= ~(0x0FU << (4U * (pin & 0x03U)));
                tmp_reg |= ((uint32_t)(PORT_GET_INDEX(ConfigPtr->Port)) << (4U * (pin & 0x03U)));
                SYSCFG->EXTICR[pin >> 2U] = tmp_reg;

                /* Configure Rising edge */
                tmp_reg = EXTI->RTSR;
                tmp_reg &= ~(1 << pin);
                if ((ConfigPtr->Mode & TRIGGER_RISING) != 0)
                    tmp_reg |= (1 << pin);
                EXTI->RTSR = tmp_reg;

                /* Configure Falling edge */
                tmp_reg = EXTI->FTSR;
                tmp_reg &= ~(1 << pin);
                if ((ConfigPtr->Mode & TRIGGER_FALLING) != 0)
                    tmp_reg |= (1 << pin);
                EXTI->FTSR = tmp_reg;

                /* Configure Event */
                tmp_reg = EXTI->EMR;
                tmp_reg &= ~(1 << pin);
                if ((ConfigPtr->Mode & EXTI_EVT) != 0)
                    tmp_reg |= (1 << pin);
                EXTI->EMR = tmp_reg;

                /* Configure Interrupt */
                tmp_reg = EXTI->IMR;
                tmp_reg &= ~(1 << pin);
                if ((ConfigPtr->Mode & EXTI_IT) != 0)
                    tmp_reg |= (1 << pin);
                EXTI->IMR = tmp_reg;
            }
        }
    }
    if (err)
        return E_NOK;
    return E_OK;
}

uint8_t Port_DeInit(const Port_ConfigType *ConfigPtr)
{
    uint32_t pin = 0;
    Port_PinType pin_pos = 0;
    Port_PinType cfg_pin_pos = 0;
    uint32_t tmp_reg = 0;

    if (!(IS_GPIO_ALL_INSTANCE(ConfigPtr->Port)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_PORT;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_DEINIT;
        Error_Code_Index++;
        return E_NOK;
    }

    for (pin = 0; pin < 16; pin++)
    {
        pin_pos = 1 << pin;
        cfg_pin_pos = pin & ConfigPtr->Pin;

        if (pin_pos == cfg_pin_pos)
        {
            tmp_reg = SYSCFG->EXTICR[pin >> 2];
            tmp_reg &= (0xFu << ((pin & 0x3u) * 4));

            /* Check for Interrupt Config */
            if (tmp_reg == ((uint32_t)(PORT_GET_INDEX(ConfigPtr->Port)) << (4U * (pin & 0x03U))))
            {
                /* Clear all interrupt and Event bits */
                EXTI->EMR &= ~(1 << pin);
                EXTI->IMR &= ~(1 << pin);

                /* Clear rising and falling edge */
                EXTI->FTSR &= ~(1 << pin);
                EXTI->RTSR &= ~(1 << pin);

                /* Clear Interrupt Config */
                tmp_reg = (0xfu << (pin & 3u) * 4u);
                SYSCFG->EXTICR[pin >> 2] &= ~tmp_reg;
            }
            /*------------------------- GPIO Mode Configuration --------------------*/
            /* Configure IO Direction in Input Floating Mode */
            ConfigPtr->Port->MODER &= ~(3U << (pin * 2U));

            /* Configure the default Alternate Function in current IO */
            ConfigPtr->Port->AFR[pin >> 3U] &= ~(0xFU << ((uint32_t)(pin & 0x07U) * 4U));

            /* Deactivate the Pull-up and Pull-down resistor for the current IO */
            ConfigPtr->Port->PUPDR &= ~(3U << (pin * 2U));

            /* Configure the default value IO Output Type */
            ConfigPtr->Port->OTYPER &= ~(1U << pin);

            /* Configure the default value for IO Speed */
            ConfigPtr->Port->OSPEEDR &= ~(3U << (pin * 2U));
        }
    }
    return E_OK;
}

uint8_t Port_ReadPin(PORT_TypeDef *GPIOx, uint16_t GPIO_Pin, Port_PinState *result)
{
    Port_PinState bitstatus;
    uint8_t err = 0;

    /* Check the parameters */
    if (!(IS_GPIO_ALL_INSTANCE(GPIOx)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_PORT;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_READPIN;
        Error_Code_Index++;
        err = 1;
    }

    if (!(IS_PORT_PIN(GPIO_Pin)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_PIN;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_READPIN;
        Error_Code_Index++;
        err = 2;
    }

    if (result == NULL)
        err = 3;

    if (err)
        return E_NOK;

    if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)PORT_PIN_RESET)
    {
        bitstatus = PORT_PIN_SET;
    }
    else
    {
        bitstatus = PORT_PIN_RESET;
    }
    *result = bitstatus;
    return E_OK;
}

uint8_t Port_WritePin(PORT_TypeDef *GPIOx, uint16_t GPIO_Pin, Port_PinState PinState)
{
    uint8_t err = 0;

    /* Check the parameters */
    if (!(IS_GPIO_ALL_INSTANCE(GPIOx)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_PORT;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_WRITEPIN;
        Error_Code_Index++;
        err = 3;
    }

    if (!(IS_PORT_PIN(GPIO_Pin)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_PIN;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_WRITEPIN;
        Error_Code_Index++;
        err = 1;
    }

    if (!(IS_PORT_PIN_ACTION(PinState)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_ACTION;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_WRITEPIN;
        Error_Code_Index++;
        err = 2;
    }

    if (err)
        return E_NOK;

    if (PinState != PORT_PIN_RESET)
    {
        GPIOx->BSRR = GPIO_Pin;
    }
    else
    {
        GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
    }
    return E_OK;
}

uint8_t Port_TogglePin(PORT_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    uint32_t odr;

    /* Check the parameters */
    uint8_t err = 0;
    /* Check the parameters */
    if (!(IS_PORT_PIN(GPIO_Pin)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_PIN;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_TOGGLEPIN;
        Error_Code_Index++;
        err = 1;
    }

    if (!(IS_GPIO_ALL_INSTANCE(GPIOx)))
    {
        DET_ErrorCode[Error_Code_Index] = PORT_E_INVALID_PORT;
        DET_ModuleId[Error_Code_Index] = PORT_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = PORT_SID_TOGGLEPIN;
        Error_Code_Index++;
        err = 2;
    }

    if (err)
        return E_NOK;

    /* get current Output Data Register value */
    odr = GPIOx->ODR;

    /* Set selected pins that were at low level, and reset ones that were high */
    GPIOx->BSRR = ((odr & GPIO_Pin) << 16u) | (~odr & GPIO_Pin);

    return E_OK;
}

void Port_EXTI0_IRQHandler(Port_PinType Port_Pin)
{
    /* Check if the interrupt has Occured */
    if(EXTI->PR & Port_Pin)
    {
        /* Clear  the PR */
        EXTI->PR |= Port_Pin;
    }

    Port_EXTI0_IRQ_CB();
}

void Port_EXTI15_10_IRQHandler(Port_PinType Port_Pin)
{
    /* Check if the interrupt has Occured */
    if(EXTI->PR & Port_Pin)
    {
        /* Clear  the PR */
        EXTI->PR |= Port_Pin;
    }

    Port_EXTI15_10_IRQ_CB();
}

__attribute__((weak)) void Port_EXTI0_IRQ_CB(void)
{
    ;
}

__attribute__((weak)) void Port_EXTI15_10_IRQ_CB(void)
{
    ;
}
