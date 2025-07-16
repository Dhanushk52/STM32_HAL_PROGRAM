#include "lcd_i2c.h"

void lcd_send_internal(uint8_t data, uint8_t flags)
{
  HAL_StatusTypeDef res;
  uint8_t buf[4];
  buf[0] = (data & 0xF0) | flags | LCD_BACKLIGHT | ENABLE;
  buf[1] = (data & 0xF0) | flags | LCD_BACKLIGHT;
  buf[2] = ((data << 4) & 0xF0) | flags | LCD_BACKLIGHT | ENABLE;
  buf[3] = ((data << 4) & 0xF0) | flags | LCD_BACKLIGHT;

  res = HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, buf, 4, HAL_MAX_DELAY);
  HAL_Delay(1);
}

void lcd_send_cmd(uint8_t cmd)
{
  lcd_send_internal(cmd, 0x00);
}

void lcd_send_data(uint8_t data)
{
  lcd_send_internal(data, 0x01);
}

void lcd_send_string(char *str)
{
  while (*str)
  {
    lcd_send_data((uint8_t)(*str));
    str++;
  }
}

void lcd_init(void)
{
  HAL_Delay(50); // LCD Power ON delay

  lcd_send_cmd(0x33); // Initialization
  lcd_send_cmd(0x32); // Set to 4-bit mode
  lcd_send_cmd(0x28); // 2-line, 5x8 matrix
  lcd_send_cmd(0x0C); // Display ON, Cursor OFF
  lcd_send_cmd(0x06); // Increment cursor
  lcd_send_cmd(0x01); // Clear display
  HAL_Delay(2);
}
