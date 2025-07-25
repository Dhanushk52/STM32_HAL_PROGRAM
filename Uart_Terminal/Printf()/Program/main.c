#include "main.h"
#include "stdio.h"

UART_HandleTypeDef huart1;  // UART handle from CubeMX

// Redirect printf to UART
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    printf("UART printf example started!\r\n");

    while (1)
    {
        printf("Hello from STM32!\r\n");
        HAL_Delay(1000);
    }
}
