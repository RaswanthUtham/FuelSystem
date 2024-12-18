#include <stdint.h>
#include "stm32xxxx.h"
#include "stm32f4xx_hal_port.h"
#include "stm32f4xx_hal_spi.h"
#include "st7735_lcd_driver.h"

static void delay(uint32_t x);
int16_t _width;       ///< Display width as modified by current rotation
int16_t _height;      ///< Display height as modified by current rotation
int16_t cursor_x;     ///< x location to start print()ing text
int16_t cursor_y;     ///< y location to start print()ing text
uint8_t rotation;     ///< Display rotation (0 thru 3)
uint8_t _colstart;   ///< Some displays need this changed to offset
uint8_t _rowstart;       ///< Some displays need this changed to offset
uint8_t _xstart;
uint8_t _ystart;

const uint8_t
    init_cmds1[] = {           // Init for 7735R, part 1 (red or green tab)
        15,                    // 15 commands in list:
        ST7735_SWRESET, DELAY, //  1: Software reset, 0 args, w/delay
        150,                   //     150 ms delay
        ST7735_SLPOUT, DELAY,  //  2: Out of sleep mode, 0 args, w/delay
        255,                   //     500 ms delay
        ST7735_FRMCTR1, 3,     //  3: Frame rate ctrl - normal mode, 3 args:
        0x01, 0x2C, 0x2D,      //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
        ST7735_FRMCTR2, 3,     //  4: Frame rate control - idle mode, 3 args:
        0x01, 0x2C, 0x2D,      //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
        ST7735_FRMCTR3, 6,     //  5: Frame rate ctrl - partial mode, 6 args:
        0x01, 0x2C, 0x2D,      //     Dot inversion mode
        0x01, 0x2C, 0x2D,      //     Line inversion mode
        ST7735_INVCTR, 1,      //  6: Display inversion ctrl, 1 arg, no delay:
        0x07,                  //     No inversion
        ST7735_PWCTR1, 3,      //  7: Power control, 3 args, no delay:
        0xA2,
        0x02,             //     -4.6V
        0x84,             //     AUTO mode
        ST7735_PWCTR2, 1, //  8: Power control, 1 arg, no delay:
        0xC5,             //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
        ST7735_PWCTR3, 2, //  9: Power control, 2 args, no delay:
        0x0A,             //     Opamp current small
        0x00,             //     Boost frequency
        ST7735_PWCTR4, 2, // 10: Power control, 2 args, no delay:
        0x8A,             //     BCLK/2, Opamp current small & Medium low
        0x2A,
        ST7735_PWCTR5, 2, // 11: Power control, 2 args, no delay:
        0x8A, 0xEE,
        ST7735_VMCTR1, 1, // 12: Power control, 1 arg, no delay:
        0x0E,
        ST7735_INVOFF, 0, // 13: Don't invert display, no args, no delay
        ST7735_COLMOD, 1, // 15: set color mode, 1 arg, no delay:
        0x05};            //     16-bit color

#if (defined(ST7735_IS_128X128) || defined(ST7735_IS_160X128))
init_cmds2[] = {     // Init for 7735R, part 2 (1.44" display)
    2,               //  2 commands in list:
    ST7735_CASET, 4, //  1: Column addr set, 4 args, no delay:
    0x00, 0x00,      //     XSTART = 0
    0x00, 0x7F,      //     XEND = 127
    ST7735_RASET, 4, //  2: Row addr set, 4 args, no delay:
    0x00, 0x00,      //     XSTART = 0
    0x00, 0x7F};     //     XEND = 127
#endif               // ST7735_IS_128X128

init_cmds3[] = {        // Init for 7735R, part 3 (red or green tab)
    4,                  //  4 commands in list:
    ST7735_GMCTRP1, 16, //  1: Magical unicorn dust, 16 args, no delay:
    0x02, 0x1c, 0x07, 0x12,
    0x37, 0x32, 0x29, 0x2d,
    0x29, 0x25, 0x2B, 0x39,
    0x00, 0x01, 0x03, 0x10,
    ST7735_GMCTRN1, 16, //  2: Sparkles and rainbows, 16 args, no delay:
    0x03, 0x1d, 0x07, 0x06,
    0x2E, 0x2C, 0x29, 0x2D,
    0x2E, 0x2E, 0x37, 0x3F,
    0x00, 0x00, 0x02, 0x10,
    ST7735_NORON, DELAY,  //  3: Normal display on, no args, w/delay
    10,                   //     10 ms delay
    ST7735_DISPON, DELAY, //  4: Main screen turn on, no args w/delay
    100};                 //     100 ms delay

static void delay(uint32_t x)
{
  for (uint32_t i = 0; i < x; i++)
    ;
}
void ST7735_Reset(st7735_ConfigType *ConfigPtr)
{
  Port_WritePin(ConfigPtr->reset_port->Port, ConfigPtr->reset_port->Pin, PORT_PIN_RESET);
  delay(2000);
  Port_WritePin(ConfigPtr->reset_port->Port, ConfigPtr->reset_port->Pin, PORT_PIN_SET);
}

void ST7735_WriteCommand(st7735_ConfigType *ConfigPtr)
{
  ConfigPtr->spi->TxSize = 1;
  Port_WritePin(ConfigPtr->dc_port->Port, ConfigPtr->dc_port->Pin, PORT_PIN_RESET);
  Spi_SyncTransmit(ConfigPtr->spi);
}

void ST7735_WriteData(st7735_ConfigType *ConfigPtr)
{
  Port_WritePin(ConfigPtr->dc_port->Port, ConfigPtr->dc_port->Pin, PORT_PIN_SET);
  Spi_SyncTransmit(ConfigPtr->spi);
}

void Init_Display(st7735_ConfigType *ConfigPtr, uint8_t *addr)
{
  uint8_t nof_cmds, num_args, cmd, data;
  uint16_t delay;

  nof_cmds = *addr++;
  while(nof_cmds--)
  {
    cmd = *addr++;
    ConfigPtr->spi->pTxBuffPtr = &cmd;
    ConfigPtr->spi->TxSize = sizeof(cmd);
    ST7735_WriteCommand(ConfigPtr);

    num_args = *addr++;
    delay = num_args & DELAY;
    num_args &= ~DELAY;

    if(num_args)
    {
      // data = *addr;
      ConfigPtr->spi->TxSize = num_args;
      ConfigPtr->spi->pTxBuffPtr = (uint8_t *)addr;
      addr += num_args;
    }

    if(delay)
    {
      delay = *addr++;
      if (delay == 255)
        delay = 500;

      /* To Do Implement Delay */
      uint32_t i = delay * 1000;
      while(i--);
    }
  }
}

void ST7735_SetAddressWindow(st7735_ConfigType *ConfigPtr, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    // column address set
    ST7735_WriteCommand(ST7735_CASET);
    uint8_t data[] = { 0x00, x0 + _xstart, 0x00, x1 + _xstart };

    ConfigPtr->spi->TxSize = sizeof(data);
    ConfigPtr->spi->pTxBuffPtr = (uint8_t *)data;
    ST7735_WriteData(ConfigPtr);

    // row address set
    ST7735_WriteCommand(ST7735_RASET);
    data[1] = y0 + _ystart;
    data[3] = y1 + _ystart;
    ConfigPtr->spi->TxSize = sizeof(data);
    ConfigPtr->spi->pTxBuffPtr = (uint8_t *)data;
    ST7735_WriteData(ConfigPtr);

    // write to RAM
    uint8_t cmd = ST7735_RAMWR;
    ConfigPtr->spi->pTxBuffPtr = &cmd;
    ST7735_WriteCommand(ConfigPtr);
}

void ST7735_Init(st7735_ConfigType *ConfigPtr, uint8_t rotation)
{
    ST7735_Reset(ConfigPtr);
    Init_Display(ConfigPtr, init_cmds1);
    Init_Display(ConfigPtr, init_cmds2);
    Init_Display(ConfigPtr, init_cmds3);
 #if ST7735_IS_160X80
    _colstart = 24;
    _rowstart = 0;
 /*****  IF Doesn't work, remove the code below (before #elif) *****/
    uint8_t data = 0xC0;
    ST7735_Select();
    ST7735_WriteCommand(ST7735_MADCTL);
    ST7735_WriteData(&data,1);

#elif ST7735_IS_128X128
    _colstart = 2;
    _rowstart = 3;
#else
    _colstart = 0;
    _rowstart = 0;
#endif
    ST7735_SetRotation(ConfigPtr, rotation);
    // ST7735_Unselect();
}

void ST7735_SetRotation(st7735_ConfigType *ConfigPtr, uint8_t m)
{
  uint8_t madctl = 0;

  rotation = m % 4; // can't be higher than 3

  switch (rotation)
  {
  case 0:
#if ST7735_IS_160X80
	  madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_BGR;
#else
      madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB;
      _height = ST7735_HEIGHT;
      _width = ST7735_WIDTH;
      _xstart = _colstart;
      _ystart = _rowstart;
#endif
    break;
  case 1:
#if ST7735_IS_160X80
	  madctl = ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_BGR;
#else
      madctl = ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
      _width = ST7735_HEIGHT;
      _height = ST7735_WIDTH;
    _ystart = _colstart;
    _xstart = _rowstart;
#endif
    break;
  case 2:
#if ST7735_IS_160X80
	  madctl = ST7735_MADCTL_BGR;
#else
      madctl = ST7735_MADCTL_RGB;
      _height = ST7735_HEIGHT;
      _width = ST7735_WIDTH;
    _xstart = _colstart;
    _ystart = _rowstart;
#endif
    break;
  case 3:
#if ST7735_IS_160X80
	  madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_BGR;
#else
      madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
      _width = ST7735_HEIGHT;
      _height = ST7735_WIDTH;
    _ystart = _colstart;
    _xstart = _rowstart;
#endif
    break;
  }
  // ST7735_Select();
  uint8_t cmd = ST7735_MADCTL;
  ConfigPtr->spi->pTxBuffPtr = &cmd;
  ST7735_WriteCommand(ConfigPtr);

  ConfigPtr->spi->pTxBuffPtr = &madctl;
  ConfigPtr->spi->pTxBuffPtr = 1;
  ST7735_WriteData(ConfigPtr);
  // ST7735_Unselect();
}

void ST7735_DrawPixel(st7735_ConfigType *ConfigPtr, uint16_t x, uint16_t y, uint16_t color) 
{
    if((x >= _width) || (y >= _height))
        return;

    // ST7735_Select();

    ST7735_SetAddressWindow(ConfigPtr, x, y, x+1, y+1);
    uint8_t data[] = { color >> 8, color & 0xFF };
    ConfigPtr->spi->TxSize = sizeof(data);
    ConfigPtr->spi->pTxBuffPtr = (uint8_t*)data;
    ST7735_WriteData(ConfigPtr);

    // ST7735_Unselect();
}

void ST7735_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor) 
{
    uint32_t i, b, j;

    ST7735_SetAddressWindow(x, y, x+font.width-1, y+font.height-1);

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                uint8_t data[] = { color >> 8, color & 0xFF };
                ST7735_WriteData(data, sizeof(data));
            } else {
                uint8_t data[] = { bgcolor >> 8, bgcolor & 0xFF };
                ST7735_WriteData(data, sizeof(data));
            }
        }
    }
}