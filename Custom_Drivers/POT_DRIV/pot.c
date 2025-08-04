#include "pot.h"

extern ADC_HandleTypeDef hadc1;  // Declare ADC handle (CubeMX generates it)

void pot_init(void)
{
    HAL_ADC_Start(&hadc1);  // Optional if you want to start once
}

uint16_t pot_read_raw(void)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(&hadc1);  // 0 to 4095 for 12-bit ADC
}

float pot_read_voltage(void)
{
    uint16_t raw = pot_read_raw();
    float voltage = (3.3f * raw) / 4095.0f;  // STM32 supply assumed as 3.3V
    return voltage;
}
