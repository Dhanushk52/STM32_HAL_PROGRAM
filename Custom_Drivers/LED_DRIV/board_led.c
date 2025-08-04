#include "board_led.h"
#include "stm32f1xx_hal.h"


void board_led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	    __HAL_RCC_GPIOC_CLK_ENABLE();

	    GPIO_InitStruct.Pin = GPIO_PIN_13;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void board_led_On(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // RESET IN ON FNC BECAUSE IT IS INVERSE
}

void board_led_Off(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);// ALSO AS OPPOSITE TO ON LED
}

void board_led_Toggle(void)
{
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

