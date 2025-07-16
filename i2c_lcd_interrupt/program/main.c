volatile uint8_t btn_pressed_flag = 0;
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();

  lcd_init();
  lcd_send_string("Interrupt Ready");

  while (1)
  {
    if (btn_pressed_flag)
    {
      btn_pressed_flag = 0;

      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
      lcd_send_cmd(0x01);         // Clear LCD
      HAL_Delay(2);               // Give LCD time to clear
      lcd_send_string("Btn Pressed!");
      HAL_Delay(1000);            // Show for 1s
      lcd_send_cmd(0x01);         // Clear again
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);	
      lcd_send_string("Interrupt Ready");
    }
  }
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_0)
  {
    btn_pressed_flag = 1;  // Just set flag!
  }
}
