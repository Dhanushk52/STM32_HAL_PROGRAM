#include "board_gas_sensor.h"

extern ADC_HandleTypeDef hadc1;  // Use CubeMX-defined ADC instance

// Assuming DO pin is connected to GPIOB Pin 1 (example)
#define MQ4_DO_PORT GPIOB
#define MQ4_DO_PIN  GPIO_PIN_1

void gas_sensor_init(void)
{
    HAL_ADC_Start(&hadc1);  // Start ADC once (optional, can also be started per read)
    // No need to configure GPIO here if CubeMX does it
}

uint16_t gas_sensor_read_raw(void)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(&hadc1);  // Returns 0–4095 (for 12-bit)
}

float gas_sensor_read_voltage(void)
{
    uint16_t raw = gas_sensor_read_raw();
    return (3.3f * raw) / 4095.0f;
}

uint8_t gas_sensor_read_digital(void)
{
    return HAL_GPIO_ReadPin(MQ4_DO_PORT, MQ4_DO_PIN);
}
