#include "main.h"

extern TIM_HandleTypeDef htim1;  // Declared in tim.h and defined in tim.c

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM1_Init();

  // Start PWM on TIM1 Channel 1
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  while (1)
  {
    // Fade effect: gradually increase duty cycle
    for (uint16_t duty = 0; duty <= 1000; duty += 20)
    {
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty);
      HAL_Delay(10);
    }

    // Then gradually decrease duty cycle
    for (uint16_t duty = 1000; duty > 0; duty -= 20)
    {
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty);
      HAL_Delay(10);
    }
  }
}
