#include "gpio_driver.h"

void GPIO_InitPin(GPIO_TypeDef* port, uint16_t pin, GPIO_Direction_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable clock for the correct port
    if (port == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    else if (port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    else if (port == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStruct.Pin = pin;

    if (mode == GPIO_MODE_OUTPUT) {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    } else {
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    }

    HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void GPIO_WritePin(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState state)
{
    HAL_GPIO_WritePin(port, pin, state);
}

void GPIO_TogglePin(GPIO_TypeDef* port, uint16_t pin)
{
    HAL_GPIO_TogglePin(port, pin);
}

GPIO_PinState GPIO_ReadPin(GPIO_TypeDef* port, uint16_t pin)
{
    return HAL_GPIO_ReadPin(port, pin);
}
