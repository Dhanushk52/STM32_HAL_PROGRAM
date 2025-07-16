#include "main.h"
#include "lcd_i2c_dma.h"

extern I2C_HandleTypeDef hi2c1;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_DMA_Init(); // Important: Enable DMA controller

  lcd_init();
  lcd_send_string_dma("DMA LCD Hello!");

  while (1)
  {
    // LCD message was already sent via DMA
    // Nothing to do here
  }
}
