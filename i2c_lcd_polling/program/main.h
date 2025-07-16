#include "main.h"
#include "lcd_i2c.h"

extern I2C_HandleTypeDef hi2c1;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();

  lcd_init();                     // Initialize LCD
  lcd_send_string("Hello Boss!"); // Line 1

  lcd_send_cmd(0xC0);             // Move to second line
  lcd_send_string("STM32 + I2C"); // Line 2

  while (1)
  {
    // Loop here; LCD content static
  }
}
