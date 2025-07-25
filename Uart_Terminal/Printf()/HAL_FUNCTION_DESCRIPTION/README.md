---

### 🧠 Concept Summary:

We **redirect `printf()`** to send data through **UART** by modifying the `__io_putchar()` or `fputc()` function so that standard output from `printf()` goes to UART instead of the debugger.

---

### 🔧 Common HAL Functions Used:

#### 1. `HAL_UART_Transmit()`

* **Header File:** `stm32f1xx_hal_uart.h`

* **Purpose:** Transmits data in blocking mode (polling).

* **Prototype:**

  ```c
  HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
  ```

* **Parameters:**

  * `huart`: Pointer to `UART_HandleTypeDef` (e.g. `&huart1`)
  * `pData`: Pointer to the byte array to transmit
  * `Size`: Number of bytes to transmit
  * `Timeout`: Time to wait before timeout (in ms)

* **Returns:**

  * `HAL_OK`, `HAL_ERROR`, `HAL_BUSY`, or `HAL_TIMEOUT`

---

### 🖨️ `printf()` Redirection Setup

In `retarget.c` or in `main.c`:

#### Option 1: For `Keil / ARMCC` or `STM32CubeIDE`

```c
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
```

#### Option 2: For `GCC / Newlib`

```c
int fputc(int ch, FILE *f) {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
```

> ✅ This allows `printf("Hello\n")` to work automatically via UART1.

---

### 🧪 Example Usage

```c
printf("Hello from STM32 via UART!\r\n");
```

---

### 📎 Notes:

* Ensure that UART is initialized (e.g., `MX_USART1_UART_Init()` must be called before using `printf()`).
* `HAL_UART_Transmit()` is blocking; use `DMA` or `Interrupt` for non-blocking behavior.

---

