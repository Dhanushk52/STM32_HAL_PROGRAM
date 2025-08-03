#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "stm32f1xx_hal.h"

typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT
} GPIO_Direction_t;

void GPIO_InitPin(GPIO_TypeDef* port, uint16_t pin, GPIO_Direction_t mode);
void GPIO_WritePin(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState state);
void GPIO_TogglePin(GPIO_TypeDef* port, uint16_t pin);
GPIO_PinState GPIO_ReadPin(GPIO_TypeDef* port, uint16_t pin);

#endif
