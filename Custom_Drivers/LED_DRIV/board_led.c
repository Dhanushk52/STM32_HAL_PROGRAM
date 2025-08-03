#include "board_led.h"

void LED_RED_On(void)
{
    GPIO_WritePin(RedledsPort, RedLedsPin, GPIO_PIN_SET);
}

void LED_RED_Off(void)
{
    GPIO_WritePin(RedledsPort, RedLedsPin, GPIO_PIN_RESET);
}

void LED_RED_Toggle(void)
{
    GPIO_TogglePin(RedledsPort, RedLedsPin);
}
