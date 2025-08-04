#include "stm32f1xx_hal.h"
#include "board_led.h"
#include "button_read.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1)
    {
        if (is_button_pressed())
        {
            board_led_On(); // include board_led files for this fnc
        }
        else
        {
            board_led_Off(); // include board_led files for this fnc
        }

        HAL_Delay(10);  // debounce or polling delay
    }
}
