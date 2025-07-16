
---

# 📘 HAL Library – UART Transmit using DMA + Timer Interrupt

This guide explains the HAL functions used to **transmit UART messages using DMA** triggered by a **timer interrupt**. CPU stays free for other tasks like blinking LEDs or sensor handling.

---

## 🔹 1. `HAL_TIM_Base_Start_IT()`

### ✅ **Purpose**

Starts the timer in interrupt mode. When the timer reaches its `Period`, it triggers **`HAL_TIM_PeriodElapsedCallback()`**.

### 🧠 **Prototype**

```c
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
```

### 🧾 **Parameters**

| Parameter | Description                                  |
| --------- | -------------------------------------------- |
| `*htim`   | Pointer to the timer handle (e.g., `&htim2`) |

### ✅ **Example**

```c
HAL_TIM_Base_Start_IT(&htim2);
```

### 🎯 **Expected Outcome**

Fires an interrupt every 3 seconds (as set by timer config), triggering the UART DMA transfer.


## 🔹 2. `HAL_TIM_PeriodElapsedCallback()`

### ✅ **Purpose**

A **user-defined interrupt service routine (ISR)** called **automatically** when the timer reaches its period value.

### 🧠 **Prototype**

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
```

### 🧾 **Parameters**

| Parameter | Description                                   |
| --------- | --------------------------------------------- |
| `*htim`   | Points to the timer that caused the interrupt |

### ✅ **Example**

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    HAL_UART_Transmit_DMA(&huart1, (uint8_t*)dma_msg, strlen(dma_msg));
  }
}
```

### 🎯 **Expected Outcome**

Every 3 seconds (as configured in TIM2), this function is triggered and initiates a **non-blocking DMA UART transmission**.

---

## 🔹 3. `HAL_UART_Transmit_DMA()`

### ✅ **Purpose**

Sends data via **UART using DMA** — CPU is free while DMA handles the transfer.

### 🧠 **Prototype**

```c
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart,
                                        uint8_t *pData,
                                        uint16_t Size);
```

### 🧾 **Parameters**

| Parameter | Description                   |
| --------- | ----------------------------- |
| `*huart`  | UART handle (e.g., `&huart1`) |
| `*pData`  | Pointer to data to transmit   |
| `Size`    | Number of bytes to send       |

### ✅ **Example**

```c
char dma_msg[] = "Hello from DMA UART!\r\n";
HAL_UART_Transmit_DMA(&huart1, (uint8_t*)dma_msg, strlen(dma_msg));
```

### 🎯 **Expected Outcome**

DMA hardware transfers the string to UART TX without CPU waiting.

---

## 🔹 4. `HAL_UART_TxCpltCallback()`

### ✅ **Purpose**

Called **automatically** when the **DMA transfer is complete** — useful to:

* Set flags
* Restart a new transfer
* Debug/check transmission

### 🧠 **Prototype**

```c
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
```

### 🧾 **Parameters**

| Parameter | Description                               |
| --------- | ----------------------------------------- |
| `*huart`  | UART instance that completed the transfer |

### ✅ **Example**

```c
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    // Optional: Set flag or blink LED
  }
}
```

### 🎯 **Expected Outcome**

This callback will execute **after DMA finishes sending data**, without disturbing main loop.

---

# 📦 Summary Table

| Function                          | Use                   | What It Does                           |
| --------------------------------- | --------------------- | -------------------------------------- |
| `HAL_TIM_Base_Start_IT()`         | Start timer interrupt | Fires callback every 3 sec             |
| `HAL_TIM_PeriodElapsedCallback()` | Timer ISR             | Initiates DMA UART send                |
| `HAL_UART_Transmit_DMA()`         | Transmit UART via DMA | Sends string non-blocking              |
| `HAL_UART_TxCpltCallback()`       | DMA ISR               | Notifies when transmission is complete |

---


