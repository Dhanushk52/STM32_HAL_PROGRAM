#ifndef BOARD_LED_H
#define BOARD_LED_H

#define BOARD_LED_PORT     GPIOC
#define BOARD_LED_PIN      GPIO_PIN_13

void board_led_init(void);
void board_led_On(void);
void board_led_Off(void);
void board_led_Toggle(void);

#endif
