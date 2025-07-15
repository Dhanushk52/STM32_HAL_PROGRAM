#include "main.h"

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ADC1_Init(void);
void MX_USART1_UART_Init(void);

ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart1;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();

  uint32_t adc_val = 0;
  char msg[50];

  while (1)
  {
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK)
    {
      adc_val = HAL_ADC_GetValue(&hadc1);
      int len = sprintf(msg, "ADC Value: %lu\r\n", adc_val);
      HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
    }
    HAL_Delay(1000); // Delay for 1 second
  }
}
