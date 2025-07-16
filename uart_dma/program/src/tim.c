#include "tim.h"

TIM_HandleTypeDef htim2;

void MX_TIM2_Init(void)
{
  __HAL_RCC_TIM2_CLK_ENABLE();

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7200 - 1;  // 10 kHz
  htim2.Init.Period = 30000 - 1;    // 3 seconds
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

  HAL_TIM_Base_Init(&htim2);

  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}
