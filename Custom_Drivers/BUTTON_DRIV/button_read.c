#include "button_read.h"

bool is_button_pressed(void)
{
    // Button pressed = logic LOW due to pull-up
    return (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_RESET);
}
