#include "stm32xxxx.h"
#include "stm32f4xx_hal_port.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_spi.h"
#include <stddef.h>

#define SPI_DEFAULT_TIMEOUT 100U
#define SPI_BSY_FLAG_WORKAROUND_TIMEOUT 1000U /*!< Timeout 1000 µs             */

static void Spi_SPI_Tx_ISR(Spi_ConfigType *ConfigPtr);
static void Spi_SPI_Rx_ISR(Spi_ConfigType *ConfigPtr);

uint8_t Spi_Init(Spi_ConfigType *ConfigPtr)
{
    uint8_t err = 0;
    if (ConfigPtr == NULL)
    {
        DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
        DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_PARAM;
        Error_Code_Index++;
        return E_NOK;
    }
    if (!IS_SPI_ALL_INSTANCE(ConfigPtr->SPI))
    {
        DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
        DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_SPI;
        Error_Code_Index++;
        return E_NOK;
    }
    if (!IS_SPI_MODE(ConfigPtr->Mode))
    {
        DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
        DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_MODE;
        Error_Code_Index++;
        err = 2;
    }
    if (!IS_SPI_DIRECTION(ConfigPtr->Direction))
    {
        DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
        DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_DIRECTION;
        Error_Code_Index++;
        err = 3;
    }
    if (!IS_SPI_DATASIZE(ConfigPtr->DataSize))
    {
        DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
        DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_DATA_SIZE;
        Error_Code_Index++;
        err = 4;
    }
    if (!IS_SPI_CS(ConfigPtr->CS))
    {
        DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
        DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_CS;
        Error_Code_Index++;
        err = 5;
    }
    if (!IS_SPI_BAUDRATE(ConfigPtr->BaudRateConfig))
    {
        DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
        DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_BAUDRATE;
        Error_Code_Index++;
        err = 6;
    }
    if (!IS_SPI_FIRST_BIT(ConfigPtr->MSB_first))
    {
        DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
        DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_MSB_FIRST;
        Error_Code_Index++;
        err = 7;
    }
    if (!IS_SPI_TI_MODE(ConfigPtr->TI_Mode))
    {
        DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
        DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_TI_MODE;
        Error_Code_Index++;
        err = 8;
    }

    if (ConfigPtr->TI_Mode == SPI_TI_MODE_DIS) /* Motorola SPI */
    {
        if (!IS_SPI_CLKPOL(ConfigPtr->ClockPolarity))
        {
            DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
            DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
            DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_CPOL;
            Error_Code_Index++;
            err = 9;
        }

        if (!IS_SPI_CLK_PHA(ConfigPtr->ClockPhase))
        {
            DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
            DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
            DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_CPHA;
            Error_Code_Index++;
            err = 10;
        }

        if (ConfigPtr->Mode == SPI_MODE_SLAVE)
        {
            /* Force Set Default Baud Rate (Baudrate prescaler not used in motorola mode) */
            ConfigPtr->BaudRateConfig = SPI_PRESCALER_2;
        }
    }
    else /* TI Mode SPI */
    {
        /* Force polarity and phase to TI protocaol requirements */
        ConfigPtr->ClockPolarity = SPI_CLK_POL_LOW;
        ConfigPtr->ClockPhase = SPI_CLK_PHASE_EDGE_1;
    }

#if (USE_SPI_CRC != 0U)
    assert_param(IS_SPI_CRC_CALCULATION(hspi->Init.CRCCalculation));
    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {
        assert_param(IS_SPI_CRC_POLYNOMIAL(hspi->Init.CRCPolynomial));
    }
#else
    ConfigPtr->CRC_Calc_Enable = SPI_CRC_CALC_DIS;
#endif /* USE_SPI_CRC */

    /* Release Resource */
    ConfigPtr->Lock = RESOURCE_RELEASE;
    ConfigPtr->SpiSupportInit(); /* Implement GPIO, CLOCK, NVIC  */

    /* To Do: Enable SPI Clock */

    ConfigPtr->Status = SPI_BUSY_INIT;
    /* Disable SPI Communication */
    ConfigPtr->SPI->CR1.B.SPE = 0;
    /* CR1 Config */
    ConfigPtr->SPI->CR1.B.CPHA = ConfigPtr->ClockPhase;
    ConfigPtr->SPI->CR1.B.CPOL = ConfigPtr->ClockPolarity;
    ConfigPtr->SPI->CR1.B.MSTR = ConfigPtr->Mode;
    ConfigPtr->SPI->CR1.B.BR = ConfigPtr->BaudRateConfig;
    ConfigPtr->SPI->CR1.B.LSBFIRST = ConfigPtr->MSB_first;
    ConfigPtr->SPI->CR1.B.SSI = ConfigPtr->Mode;
    ConfigPtr->SPI->CR1.B.SSM = ConfigPtr->CS;
    ConfigPtr->SPI->CR1.B.RXONLY = ConfigPtr->Direction;
    ConfigPtr->SPI->CR1.B.DFF = ConfigPtr->DataSize;
    ConfigPtr->SPI->CR1.B.CRCEN = ConfigPtr->CRC_Calc_Enable;
    ConfigPtr->SPI->CR1.B.BIDIMODE = !ConfigPtr->SPI->CR1.B.RXONLY;

    /* CR2 Config */
    ConfigPtr->SPI->CR2.B.FRF = ConfigPtr->TI_Mode;
    ConfigPtr->SPI->CR2.B.SSOE = ConfigPtr->MultiMaster;

#if (USE_SPI_CRC != 0U)
    if (ConfigPtr->CRC_Calc_Enable == SPI_CRC_CALC_EN)
        ConfigPtr->SPI->CRCPR = ((ConfigPtr->CRC_Poly) & 0xFFFF);
#endif /* USE_SPI_CRC */

    ConfigPtr->Status = SPI_IDLE;

    if (err)
        return E_NOK;
    return E_OK;
}

uint8_t Spi_DeInit(Spi_ConfigType *ConfigPtr)
{
    if (ConfigPtr == NULL)
    {
        DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = SPI_SID_DEINIT;
        DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_PARAM;
        Error_Code_Index++;
        return E_NOK;
    }
    if (!IS_SPI_ALL_INSTANCE(ConfigPtr->SPI))
    {
        DET_ModuleId[Error_Code_Index] = SPI_MODULE_ID;
        DET_ServiceId[Error_Code_Index] = SPI_SID_INIT;
        DET_ErrorCode[Error_Code_Index] = SPI_E_INVALID_SPI;
        Error_Code_Index++;
        return E_NOK;
    }
    ConfigPtr->Status = SPI_BUSY_DEINIT;

    /* Disable SPI Communication */
    ConfigPtr->SPI->CR1.B.SPE = 0;

    /* DeInit Low Level Drivers GPIO, SPI_CLOCK, NVIC */
    ConfigPtr->SpiSupportDeInit();

    ConfigPtr->Status = SPI_UNINIT;

    /* Release lock */
    ConfigPtr->Lock = RESOURCE_RELEASE;
    return E_OK;
}

uint8_t Spi_SyncTransmit(Spi_ConfigType *ConfigPtr)
{
    __IO uint32_t temp;

    if (ConfigPtr->Status != SPI_IDLE)
        return E_NOK;

    /* Lock Resource */
    ConfigPtr->Lock = RESOURCE_ACQUIRE;
    ConfigPtr->Status = SPI_BUSY_TX;
    ConfigPtr->pRxBuffPtr = NULL;
    ConfigPtr->RxCount = 0;
    ConfigPtr->RxSize = 0;

    /* Enable SPI Peripheral */
    if (!ConfigPtr->SPI->CR1.B.SPE)
        ConfigPtr->SPI->CR1.B.SPE = 1;

    if (ConfigPtr->DataSize == SPI_DATA_16_BIT)
    {
        ConfigPtr->TxCount = ConfigPtr->TxSize / 2;
        while (ConfigPtr->TxCount > 0)
        {
            /* wait untill TX Buffer is Empty */
            if (ConfigPtr->SPI->SR.B.TXE == 1)
            {
                ConfigPtr->SPI->DR = *(const uint16_t *)ConfigPtr->pTxBuffPtr;
                ConfigPtr->pTxBuffPtr += sizeof(uint16_t);
                ConfigPtr->TxCount--;
            }
            else
            {
                /* ToDO Implement Time Out */
            }
        }
    }
    else
    {
        ConfigPtr->TxCount = ConfigPtr->TxSize;
        while (ConfigPtr->TxCount > 0)
        {
            /* wait untill TX Buffer is Empty */
            if (ConfigPtr->SPI->SR.B.TXE == 1)
            {
                ConfigPtr->SPI->DR = *(const uint8_t *)ConfigPtr->pTxBuffPtr;
                ConfigPtr->pTxBuffPtr += sizeof(uint8_t);
                ConfigPtr->TxCount--;
            }
            else
            {
                /* ToDO Implement Time Out */
            }
        }
    }

    /* Clear Overrun Flag */
    if (ConfigPtr->Direction == SPI_FULL_DUPLEX)
    {
        temp = ConfigPtr->SPI->DR;
        temp = ConfigPtr->SPI->SR.U;
        (void)temp;
    }

    /* Release SPI */
    ConfigPtr->Status = SPI_IDLE;
    ConfigPtr->Lock = RESOURCE_RELEASE;
    return E_OK;
}

uint8_t Spi_SyncReceive(Spi_ConfigType *ConfigPtr)
{
    if (ConfigPtr->Status != SPI_IDLE)
        return E_NOK;

    if ((ConfigPtr->Mode == SPI_MODE_MASTER) && (ConfigPtr->Direction == SPI_FULL_DUPLEX))
    {
        ConfigPtr->Status = SPI_BUSY_RX;
        return Spi_SyncTransmitReceive(ConfigPtr);
    }
    return E_OK;
}

uint8_t Spi_SyncTransmitReceive(Spi_ConfigType *ConfigPtr)
{
    ConfigPtr->Lock = RESOURCE_ACQUIRE;

    uint8_t RxTx = 1; /* Used to Transmit and Receive Sequencialy */

    if (ConfigPtr->Status != SPI_BUSY_RX)
        ConfigPtr->Status = SPI_BUSY_RX_TX;

    if (ConfigPtr->DataSize == SPI_DATA_16_BIT)
    {
        ConfigPtr->TxCount = ConfigPtr->TxSize / 2;
        while ((ConfigPtr->TxCount > 0) || (ConfigPtr->RxCount > 0))
        {
            /* Check TXE Flage */
            if ((1 == ConfigPtr->SPI->SR.B.TXE) && (ConfigPtr->TxCount > 0) && (1 == RxTx))
            {
                ConfigPtr->SPI->DR = *(const uint16_t *)ConfigPtr->pTxBuffPtr;
                ConfigPtr->pTxBuffPtr += sizeof(uint16_t);
                ConfigPtr->TxCount--;
                RxTx = 0; /* Receiving After Transmission */
            }
            /* Check RxNE flag */
            if ((1 == ConfigPtr->SPI->SR.B.RXNE) && (ConfigPtr->RxCount > 0) && (0 == RxTx))
            {
                *ConfigPtr->pRxBuffPtr = (uint16_t)ConfigPtr->SPI->DR;
                ConfigPtr->pRxBuffPtr += sizeof(uint16_t);
                ConfigPtr->RxCount--;
                RxTx = 1;
            }
        }
    }
    else
    {
        ConfigPtr->TxCount = ConfigPtr->TxSize;
        while ((ConfigPtr->TxCount > 0) || (ConfigPtr->RxCount > 0))
        {
            /* Check TXE Flage */
            if ((1 == ConfigPtr->SPI->SR.B.TXE) && (ConfigPtr->TxCount > 0) && (1 == RxTx))
            {
                ConfigPtr->SPI->DR = *(const uint8_t *)ConfigPtr->pTxBuffPtr;
                ConfigPtr->pTxBuffPtr += sizeof(uint8_t);
                ConfigPtr->TxCount--;
                RxTx = 0; /* Receiving After Transmission */
            }
            /* Check RxNE flag */
            if ((1 == ConfigPtr->SPI->SR.B.RXNE) && (ConfigPtr->RxCount > 0) && (0 == RxTx))
            {
                *ConfigPtr->pRxBuffPtr = (uint8_t)ConfigPtr->SPI->DR;
                ConfigPtr->pRxBuffPtr += sizeof(uint8_t);
                ConfigPtr->RxCount--;
                RxTx = 1;
            }
        }
    }

    ConfigPtr->Status = SPI_IDLE;
    ConfigPtr->Lock = RESOURCE_RELEASE;
    return E_OK;
}

uint8_t Spi_AsyncTransmitIt(Spi_ConfigType *ConfigPtr)
{
    ConfigPtr->Lock = RESOURCE_ACQUIRE;

    ConfigPtr->Status = SPI_BUSY_TX;
    if (ConfigPtr->SPI->CR1.B.SPE == 0)
        ConfigPtr->SPI->CR1.B.SPE = 1;

    ConfigPtr->Lock = RESOURCE_RELEASE;

    /* Enable TXEIE Interrupt */
    ConfigPtr->SPI->CR2.B.TXEIE = 1;
    ConfigPtr->SPI->CR2.B.ERRIE = 1;

    return E_OK;
}

void Spi_SPI_IRQHandler(Spi_ConfigType *ConfigPtr)
{
    if ((ConfigPtr->SPI->SR.B.TXE == 1) && (ConfigPtr->SPI->CR2.B.TXEIE == 1))
    {
        Spi_SPI_Tx_ISR(ConfigPtr);
    }

    if ((ConfigPtr->SPI->SR.B.RXNE == 1) && (ConfigPtr->SPI->CR2.B.RXNEIE == 1))
    {
        Spi_SPI_Rx_ISR(ConfigPtr);
    }
}

static void Spi_SPI_Tx_ISR(Spi_ConfigType *ConfigPtr)
{
    if (ConfigPtr->DataSize == SPI_DATA_16_BIT)
    {
        ConfigPtr->SPI->DR = *(uint16_t *)ConfigPtr->pTxBuffPtr;
        ConfigPtr->pTxBuffPtr += sizeof(uint16_t);
        ConfigPtr->TxCount--;
    }
    if (ConfigPtr->DataSize == SPI_DATA_8_BIT)
    {
        ConfigPtr->SPI->DR = *(uint8_t *)ConfigPtr->pTxBuffPtr;
        ConfigPtr->pTxBuffPtr++;
        ConfigPtr->TxCount--;
    }
    if (ConfigPtr->TxCount == 0)
    {
        ConfigPtr->SPI->CR2.B.TXEIE = 0;
        if (ConfigPtr->SpiEventCallBack != NULL)
            ConfigPtr->SpiEventCallBack(SPI_TX_COMPLETE);
    }
}

static void Spi_SPI_Rx_ISR(Spi_ConfigType *ConfigPtr)
{
    if (ConfigPtr->DataSize == SPI_DATA_16_BIT)
    {
        *(uint16_t *)ConfigPtr->pTxBuffPtr = (uint16_t)ConfigPtr->SPI->DR;
        ConfigPtr->pRxBuffPtr += sizeof(uint16_t);
        ConfigPtr->RxCount--;
    }
    if (ConfigPtr->DataSize == SPI_DATA_8_BIT)
    {
        ConfigPtr->SPI->DR = *(uint8_t *)ConfigPtr->pTxBuffPtr;
        ConfigPtr->pTxBuffPtr++;
        ConfigPtr->TxCount--;
    }
    if (ConfigPtr->TxCount == 0)
    {
        ConfigPtr->SPI->CR2.B.TXEIE = 0;
        if (ConfigPtr->SpiEventCallBack != NULL)
            ConfigPtr->SpiEventCallBack(SPI_TX_COMPLETE);
    }
}