#ifndef BOARD_LCD_H
#define BOARD_LCD_H

#include "stm32f1xx_hal.h"

// Define I2C handle and LCD address
#define LCD_I2C_ADDR        (0x27 << 1)  // Shifted for HAL (7-bit << 1)
extern I2C_HandleTypeDef hi2c1;         // Defined in main or elsewhere

// LCD Commands
void lcd_init(void);
void lcd_clear(void);
void lcd_goto(uint8_t row, uint8_t col);
void lcd_send_string(char *str);
void lcd_send_char(char ch);

#endif
