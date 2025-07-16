
# 📘 HAL Library – UART + Timer Interrupt

---

## 🔹 1. `HAL_TIM_Base_Start_IT()`

### ✅ **Purpose**

Starts the timer in **interrupt mode** — the timer will overflow (or reach a set value), and **trigger an interrupt automatically**.

### 🧠 **Prototype**

```c
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
```

### 🧾 **Parameters**

| Parameter | Description                                      |
| --------- | ------------------------------------------------ |
| `*htim`   | Pointer to your timer handle (`&htim2` for TIM2) |

### ✅ **Example**

```c
HAL_TIM_Base_Start_IT(&htim2);
```

### 🎯 **Expected Outcome**

* Starts TIM2
* Every time TIM2 reaches its `Period` value, an **interrupt** will trigger, and **`HAL_TIM_PeriodElapsedCallback()`** will run.

---

## 🔹 2. `HAL_TIM_PeriodElapsedCallback()`

### ✅ **Purpose**

User-defined **callback function** that HAL automatically calls when a timer interrupt occurs (i.e., timer reaches overflow).

### 🧠 **Prototype**

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
```

### 🧾 **Parameters**

| Parameter | Description                                      |
| --------- | ------------------------------------------------ |
| `*htim`   | Points to the timer that triggered the interrupt |

### ✅ **Example**

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    // This runs every 3 seconds
  }
}
```

### 🎯 **Expected Outcome**

* Called automatically when TIM2 overflows
* You can **send UART**, toggle GPIO, etc. inside

---

## 🔹 3. `HAL_UART_Transmit()`

### ✅ **Purpose**

Sends data **via UART** (blocking function) — waits until all bytes are sent.

### 🧠 **Prototype**

```c
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart,
                                    uint8_t *pData,
                                    uint16_t Size,
                                    uint32_t Timeout);
```

### 🧾 **Parameters**

| Parameter | Description                              |
| --------- | ---------------------------------------- |
| `*huart`  | Pointer to UART handle (e.g., `&huart1`) |
| `*pData`  | Pointer to data buffer to send           |
| `Size`    | Number of bytes to send                  |
| `Timeout` | Max wait time (e.g., `HAL_MAX_DELAY`)    |

### ✅ **Example**

```c
char msg[] = "Timer Interrupt Triggered\r\n";
HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
```

### 🎯 **Expected Outcome**

* Sends the string over USART1 TX pin (PA9)
* Data will appear in Serial Terminal (PC)

---

# 📦 Summary Table

| Function                          | Description                    | Where Used        |
| --------------------------------- | ------------------------------ | ----------------- |
| `HAL_TIM_Base_Start_IT()`         | Starts timer in interrupt mode | `main()`          |
| `HAL_TIM_PeriodElapsedCallback()` | ISR runs on timer overflow     | Interrupt routine |
| `HAL_UART_Transmit()`             | Sends UART message to PC       | Inside timer ISR  |

---

