#ifndef __LCD_DRIVER_H__
#define __LCD_DRIVER_H__

typedef struct {
    const uint8_t width;
    uint8_t height;
    const uint16_t *data;
} FontDef;


extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;

typedef struct
{
    Spi_ConfigType *spi;
    Port_ConfigType *dc_port; /* data or command pin */
    Port_ConfigType *reset_port;
}st7735_ConfigType;

extern Spi_ConfigType st7735_lcd_spi;
#define ST7735_SPI_PORT st7735_lcd_spi

/* TFT DISPLAY SIZE */
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160

#define DELAY 0x80

#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MV  0x20
#define ST7735_MADCTL_ML  0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH  0x04

/* TFT DISPLAY COMMANDS */
#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01 /* SW Reset */
#define ST7735_RDDID   0x04 /* Read Display ID */
#define ST7735_RDDST   0x09 /* Read Display Status */

#define ST7735_SLPIN   0x10 /* Sleep Mode */
#define ST7735_SLPOUT  0x11 /* Awake */
#define ST7735_PTLON   0x12 /* Partial Awake */
#define ST7735_NORON   0x13 /* Normal Display ON */

#define ST7735_INVOFF  0x20 /* Display Inversion OFF */
#define ST7735_INVON   0x21 /* Display Inversion ON */
#define ST7735_DISPOFF 0x28 /* Display OFF */ 
#define ST7735_DISPON  0x29 /* Display ON */
#define ST7735_CASET   0x2A /* Column Address Set */
#define ST7735_RASET   0x2B /* Page Address Set */
#define ST7735_RAMWR   0x2C /* Memory Write */
#define ST7735_RAMRD   0x2E /* Memory Read */

#define ST7735_PTLAR   0x30 /* Partial Area */
#define ST7735_COLMOD  0x3A /* Pixel Format Set */
#define ST7735_MADCTL  0x36 /* Memory Access Control */

#define ST7735_FRMCTR1 0xB1 /* Frame Control Normal Mode Full Colors */
#define ST7735_FRMCTR2 0xB2 /* Frame Control Idle Mode / 8 Colors */
#define ST7735_FRMCTR3 0xB3 /* Frame Control Partial Mode / Full Colors */
#define ST7735_INVCTR  0xB4 /* Display Inversion Control */
#define ST7735_DISSET5 0xB6 /* Display Function Control */

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define color565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

#endif /* __LCD_DRIVER_H__ */