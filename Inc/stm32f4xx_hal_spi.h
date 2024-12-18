#ifndef __STM32F4XX_HAL_SPI_H__
#define __STM32F4XX_HAL_SPI_H__

#define SPI_MODULE_ID (83U)

typedef enum
{
    SPI_MODE_SLAVE,
    SPI_MODE_MASTER
} Spi_ModeConfig;
#define IS_SPI_MODE(__MODE__)   ((__MODE__ == SPI_MODE_SLAVE) || (__MODE__ == SPI_MODE_MASTER))

typedef enum
{
    SPI_FULL_DUPLEX = 0,
    SPI_RX_ONLY = 1,
    SPI_HALF_DUPLEX,
    SPI_TX_ONLY
} Spi_DirectionConfig;
#define IS_SPI_DIRECTION(__DIRECTION__) ((__DIRECTION__ == SPI_FULL_DUPLEX) || \
                                         (__DIRECTION__ == SPI_HALF_DUPLEX) || \
                                         (__DIRECTION__ == SPI_RX_ONLY) || \
                                         (__DIRECTION__ == SPI_TX_ONLY))

typedef enum
{
    SPI_DATA_8_BIT,
    SPI_DATA_16_BIT
} Spi_DataTransmitSize;
#define IS_SPI_DATASIZE(__SIZE__) ((__SIZE__ == SPI_DATA_16_BIT) || (__SIZE__ == SPI_DATA_8_BIT))

typedef enum
{
    SPI_CLK_POL_LOW,
    SPI_CLK_POL_HIGH
} Spi_ClockPolarity;
#define IS_SPI_CLKPOL(__POL__) ((__POL__ == SPI_CLK_POL_LOW) || (__POL__ == SPI_CLK_POL_HIGH))

typedef enum
{
    SPI_CLK_PHASE_EDGE_1,
    SPI_CLK_PHASE_EDGE_2
} Spi_ClockPhase;
#define IS_SPI_CLK_PHA(__PHA__) ((__PHA__ == SPI_CLK_PHASE_EDGE_1) || (SPI_CLK_PHASE_EDGE_2 == __PHA__))

typedef enum
{
    SPI_CS_HARDWARE,
    SPI_CS_SOFTWARE
} Spi_SlaveSelect;
#define IS_SPI_CS(__CS__) ((__CS__ == SPI_CS_SOFTWARE) || (SPI_CS_HARDWARE == __CS__))
 
typedef enum
{
    SPI_PRESCALER_2,
    SPI_PRESCALER_4,
    SPI_PRESCALER_8,
    SPI_PRESCALER_16,
    SPI_PRESCALER_32,
    SPI_PRESCALER_64,
    SPI_PRESCALER_128,
    SPI_PRESCALER_256
} Spi_BaudRateConfig;
#define IS_SPI_BAUDRATE(__BR__)         ((__BR__ == SPI_PRESCALER_2) || \
                                         (__BR__ == SPI_PRESCALER_4) || \
                                         (__BR__ == SPI_PRESCALER_8) || \
                                         (__BR__ == SPI_PRESCALER_16) || \
                                         (__BR__ == SPI_PRESCALER_64) || \
                                         (__BR__ == SPI_PRESCALER_32) || \
                                         (__BR__ == SPI_PRESCALER_128) || \
                                         (__BR__ == SPI_PRESCALER_256))

typedef enum
{
    SPI_UNINIT,
    SPI_IDLE,
    SPI_BUSY_RX,
    SPI_BUSY_TX,
    SPI_BUSY_RX_TX,
    SPI_BUSY_INIT,
    SPI_BUSY_DEINIT
} Spi_Status;

typedef enum
{
SPI_CRC_CALC_EN = 1,
SPI_CRC_CALC_DIS = 0
}Spi_CRCConfig;

typedef enum
{
    SPI_TX_COMPLETE,
    SPI_RX_COMPLETE,
    SPI_TIMEOUT,
    SPI_ERROR,
}SpiEventType;

typedef enum
{
    SPI_MULTIMASTER_EN,
    SPI_MULTIMASTER_DIS
}Spi_MultiMasterConfig;

#define IS_SPI_CRC_CALC(__X__) ((__X__ == SPI_CRC_CALC_EN) || (SPI_CRC_CALC_DIS == __X__))

#define SPI_MSB_FIRST (0u)
#define SPI_LSB_FIRST (1u)
#define IS_SPI_FIRST_BIT(__X__) ((__X__ == SPI_MSB_FIRST) || (SPI_LSB_FIRST == __X__))

typedef enum
{
    SPI_TI_MODE_DIS,
    SPI_TI_MODE_EN
}Spi_TIMode;
#define IS_SPI_TI_MODE(__X__) ((__X__ == SPI_TI_MODE_EN) || (SPI_TI_MODE_DIS == __X__))

typedef struct
{
    SPI_TypeDef *SPI;   /* SPI Kernel */
    Spi_ModeConfig Mode;    /* MASTER SLAVE */
    Spi_DirectionConfig Direction; /* FULL DUPLEX or HALF DUPLEX or RX ONLY or TX ONLY */
    Spi_DataTransmitSize DataSize;  /* 16 BIT or 8 BIT data */
    Spi_ClockPolarity ClockPolarity; /* CPOL */
    Spi_ClockPhase ClockPhase;  /* CPHA */
    Spi_SlaveSelect CS; /* HW-CS or SW-CS */
    Spi_BaudRateConfig BaudRateConfig;  /* Transfer SPeed */
    Spi_Status Status;  /* IDLE, BUSY, INIT Updated by Driver */
    Spi_MultiMasterConfig MultiMaster; /* Multimaster enable disable */
    Resource_Typedef Lock; /* Semaphore */
    uint8_t MSB_first; /* MSB or LSB first */
    Spi_TIMode TI_Mode; /* TI Mode or Motorola Mode */
    uint8_t CRC_Calc_Enable;
    uint8_t CRC_Poly;
    const uint8_t *pTxBuffPtr;
    uint8_t TxCount;
    uint8_t TxSize; /* Size of Data in Bytes */
    uint8_t *pRxBuffPtr;
    uint8_t RxCount;
    uint8_t RxSize;
    /* Call back functions */
    void (*SpiSupportInit)(void); /* gpio, nvic, spi clock */
    void (*SpiSupportDeInit)(void); /* gpio, nvic, spi clock */
    void (*SpiEventCallBack)(SpiEventType x); /* SPI Event Callback */
} Spi_ConfigType;

/* Error ID */
#define SPI_E_INVALID_CRC                   (1)
#define SPI_E_INVALID_MODE                  (2)
#define SPI_E_OVERRUN                       (3)
#define SPI_E_INVALID_FRAME                 (4)
#define SPI_E_INVALID_SPI                   (5)
#define SPI_E_INVALID_DIRECTION             (6)
#define SPI_E_INVALID_CS                    (7)
#define SPI_E_INVALID_BAUDRATE              (8)
#define SPI_E_INVALID_MSB_FIRST             (9)
#define SPI_E_INVALID_TI_MODE               (10)
#define SPI_E_INVALID_DATA_SIZE             (11)
#define SPI_E_INVALID_CPOL                  (12)
#define SPI_E_INVALID_CPHA                  (13)
#define SPI_E_INVALID_PARAM                 (14)

/* Service ID */
#define SPI_SID_INIT                                    (1)
#define SPI_SID_DEINIT                                  (2)
#define SPI_SID_SYNC_TRANSMIT                           (3)
#define SPI_SID_SYNC_RECEIVE                            (4)
#define SPI_SID_SYNC_TRANSMIT_RECEIVE                   (5)


uint8_t Spi_Init(Spi_ConfigType *ConfigPtr);
uint8_t Spi_DeInit(Spi_ConfigType *ConfigPtr);
uint8_t Spi_SyncTransmit(Spi_ConfigType *ConfigPtr);
uint8_t Spi_SyncReceive(Spi_ConfigType *ConfigPtr);
uint8_t Spi_SyncTransmitReceive(Spi_ConfigType *ConfigPtr);
uint8_t Spi_AsyncTransmitIt(Spi_ConfigType *ConfigPtr);

void Spi_SPI_IRQHandler(Spi_ConfigType *ConfigPtr);


#endif /* __STM32F4XX_HAL_SPI_H__ */
