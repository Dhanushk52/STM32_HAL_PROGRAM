#include "main.h"

extern TIM_HandleTypeDef htim2;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();

  // Start timer in interrupt mode
  HAL_TIM_Base_Start_IT(&htim2);

  while (1)
  {
    // Main loop does nothing — LED toggled in ISR
  }
}

// Timer interrupt callback function (defined by HAL)
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Toggle LED on PA5
  }
}
