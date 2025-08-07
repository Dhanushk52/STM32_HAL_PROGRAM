#ifndef BOARD_GAS_SENSOR_H
#define BOARD_GAS_SENSOR_H

#include "stm32f1xx_hal.h"

void gas_sensor_init(void);

uint16_t gas_sensor_read_raw(void);

float gas_sensor_read_voltage(void);

uint8_t gas_sensor_read_digital(void);

#endif
