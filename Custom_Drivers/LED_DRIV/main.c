#include "board_led.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    board_led_init();  // Initialize the Onboard LED
    
    while (1)
    {
      board_led_Toggle();
      HAL_Delay(500);  
    }
}
