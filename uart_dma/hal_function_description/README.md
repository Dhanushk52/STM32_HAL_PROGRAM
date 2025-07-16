
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

---

## 🔹 2. `HAL_TIM_PeriodElapsedCallback()`

### ✅ **Purpose**

This is a **user-defined callback** function called automatically when the timer over
