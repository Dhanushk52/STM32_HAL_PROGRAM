#include "pot.h"
#include "board_lcd.h"  // Optional if you want to show pot value

char buffer[20];

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    pot_init();

    while (1)
    {
        uint16_t raw = pot_read_raw();
        float voltage = pot_read_voltage();

        // Example printing (replace with UART/LCD)
        sprintf(buffer, "Raw: %u", raw);
        // lcd_send_string(buffer);

        sprintf(buffer, "V: %.2f", voltage);
        // lcd_send_string(buffer);

        HAL_Delay(500);
    }
}
