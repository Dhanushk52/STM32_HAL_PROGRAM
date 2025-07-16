#include "lcd_i2c_dma.h"

static uint8_t lcd_buf[4];

void lcd_send_internal_dma(uint8_t data, uint8_t flags)
{
  lcd_buf[0] = (data & 0xF0) | flags | LCD_BACKLIGHT | ENABLE;
  lcd_buf[1] = (data & 0xF0) | flags | LCD_BACKLIGHT;
  lcd_buf[2] = ((data << 4) & 0xF0) | flags | LCD_BACKLIGHT | ENABLE;
  lcd_buf[3] = ((data << 4) & 0xF0) | flags | LCD_BACKLIGHT;

  // DMA Transmit
  HAL_I2C_Master_Transmit_DMA(&hi2c1, LCD_ADDR, lcd_buf, 4);

  // Wait for transfer to finish
  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
  HAL_Delay(1);
}

void lcd_send_cmd_dma(uint8_t cmd)
{
  lcd_send_internal_dma(cmd, 0x00);
}

void lcd_send_data_dma(uint8_t data)
{
  lcd_send_internal_dma(data, 0x01);
}

void lcd_send_string_dma(char *str)
{
  while (*str)
  {
    lcd_send_data_dma((uint8_t)(*str++));
  }
}

void lcd_init(void)
{
  HAL_Delay(50); // Power ON delay

  lcd_send_cmd_dma(0x33); // Init
  lcd_send_cmd_dma(0x32); // 4-bit
  lcd_send_cmd_dma(0x28); // 2 line
  lcd_send_cmd_dma(0x0C); // Display on
  lcd_send_cmd_dma(0x06); // Cursor inc
  lcd_send_cmd_dma(0x01); // Clear
  HAL_Delay(2);
}
