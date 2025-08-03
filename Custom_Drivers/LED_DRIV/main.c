#include "board_led.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    // Initialize the LED
    GPIO_InitPin(RedledsPort, RedLedsPin, GPIO_MODE_OUTPUT);

    while (1)
    {
        LED_RED_Toggle();
        HAL_Delay(500);
    }
}
