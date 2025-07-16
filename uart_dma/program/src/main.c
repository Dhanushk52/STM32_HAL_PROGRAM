#include "main.h"
#include "tim.h"
#include "usart.h"

extern UART_HandleTypeDef huart1;

char dma_msg[] = "Timer DMA UART: Hello STM32!\r\n";

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();

  // Start TIM2 interrupt (we'll still use callback to trigger DMA)
  HAL_TIM_Base_Start_IT(&htim2);

  while (1)
  {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // Blink LED
    HAL_Delay(500); // Delay 500ms
  }
}

// Timer callback → trigger UART transmit using DMA
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    HAL_UART_Transmit_DMA(&huart1, (uint8_t*)dma_msg, strlen(dma_msg));
  }
}

// Optional: Callback when DMA finishes transmitting
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  // You can set a flag here if needed
}
