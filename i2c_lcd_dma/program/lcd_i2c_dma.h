#ifndef __LCD_I2C_DMA_H
#define __LCD_I2C_DMA_H

#include "stm32f1xx_hal.h"
#include "string.h"

#define LCD_ADDR       (0x27 << 1)
extern I2C_HandleTypeDef hi2c1;

#define LCD_BACKLIGHT  0x08
#define ENABLE         0x04

void lcd_send_cmd_dma(uint8_t cmd);
void lcd_send_data_dma(uint8_t data);
void lcd_send_string_dma(char *str);
void lcd_init(void);

#endif
