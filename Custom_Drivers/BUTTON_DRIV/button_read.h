#ifndef BUTTON_READ_H
#define BUTTON_READ_H

#include <stdbool.h>
#include "stm32f1xx_hal.h"

// Customize for your input pin
#define BUTTON_PORT     GPIOA
#define BUTTON_PIN      GPIO_PIN_0

bool is_button_pressed(void);  // returns true if pressed (active low logic)

#endif
