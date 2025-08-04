#include "board_lcd.h"
#include "string.h"
#include "stdint.h"

// Define LCD bit masks
#define LCD_BACKLIGHT   0x08
#define LCD_ENABLE      0x04
#define LCD_RW          0x02
#define LCD_RS          0x01

static void lcd_send_cmd(uint8_t cmd);
static void lcd_send_data(uint8_t data);
static void lcd_send_4bits(uint8_t data);
static void lcd_write_byte(uint8_t data);

void lcd_init(void)
{
    HAL_Delay(50);

    lcd_send_4bits(0x30);
    HAL_Delay(5);
    lcd_send_4bits(0x30);
    HAL_Delay(1);
    lcd_send_4bits(0x30);
    HAL_Delay(1);
    lcd_send_4bits(0x20); // 4-bit mode

    lcd_send_cmd(0x28); // 2 lines, 5x8 font
    lcd_send_cmd(0x0C); // Display ON, Cursor OFF
    lcd_send_cmd(0x06); // Entry mode
    lcd_send_cmd(0x01); // Clear display
    HAL_Delay(2);
}

void lcd_send_string(char *str)
{
    while (*str)
        lcd_send_data(*str++);
}

void lcd_send_char(char ch)
{
    lcd_send_data(ch);
}

void lcd_goto(uint8_t row, uint8_t col)
{
    uint8_t addr = (row == 0) ? 0x80 + col : 0xC0 + col;
    lcd_send_cmd(addr);
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}

// ------------------ Internal Helpers ------------------

static void lcd_send_cmd(uint8_t cmd)
{
    lcd_send_4bits((cmd & 0xF0) | LCD_BACKLIGHT);
    lcd_send_4bits(((cmd << 4) & 0xF0) | LCD_BACKLIGHT);
}

static void lcd_send_data(uint8_t data)
{
    lcd_send_4bits((data & 0xF0) | LCD_RS | LCD_BACKLIGHT);
    lcd_send_4bits(((data << 4) & 0xF0) | LCD_RS | LCD_BACKLIGHT);
}

static void lcd_send_4bits(uint8_t data)
{
    lcd_write_byte(data | LCD_ENABLE);
    HAL_Delay(1);
    lcd_write_byte(data & ~LCD_ENABLE);
    HAL_Delay(1);
}

static void lcd_write_byte(uint8_t data)
{
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, &data, 1, HAL_MAX_DELAY);
}
