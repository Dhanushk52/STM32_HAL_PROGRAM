#ifndef BOARD_LED_H
#define BOARD_LED_H

#include "gpio_driver.h"

#define RedLedsPin    GPIO_PIN_13
#define RedledsPort   GPIOC

void LED_RED_On(void);
void LED_RED_Off(void);
void LED_RED_Toggle(void);

#endif
