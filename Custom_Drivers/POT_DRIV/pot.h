#ifndef POT_H
#define POT_H

#include "stm32f1xx_hal.h"

void pot_init(void);
uint16_t pot_read_raw(void);
float pot_read_voltage(void);

#endif
