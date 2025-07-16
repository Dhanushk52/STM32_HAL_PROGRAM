#include "main.h"
#include "usart.h"
#include "tim.h"

extern UART_HandleTypeDef huart1;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();

  // Start TIM2 in interrupt mode
  HAL_TIM_Base_Start_IT(&htim2);

  while (1)
  {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // Blink PC13
    HAL_Delay(500); // Blink every 0.5s
  }
}

// This function is called automatically on timer overflow
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    char msg[] = "Timer Interrupt: Hello from STM32!\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
  }
}
