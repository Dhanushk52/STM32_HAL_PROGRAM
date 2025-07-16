# 📘 Beginner’s Guide to STM32F103C8T6 – Timer with HAL (TIM2)

---

## **1. Introduction**

Timers in STM32 allow you to generate periodic events, delays, PWM signals, or capture input signals. This section focuses on **basic timer in interrupt mode** — useful for blinking LEDs, task scheduling, etc.

---

## **2. What is a Timer?**

A timer is a peripheral that counts clock pulses. Once it reaches a defined value (Auto-Reload or Period), it can trigger an **interrupt**, toggle a pin, or reset itself.

---

## **3. Development Setup**

| Parameter  | Value                                |
| ---------- | ------------------------------------ |
| MCU        | STM32F103C8T6 (Blue Pill)            |
| IDE        | STM32CubeIDE                         |
| Timer Used | TIM2                                 |
| Purpose    | Interrupt every 500 ms to toggle LED |
| Output Pin | PA5 (LED Toggle – optional)          |

---

## **4. HAL Timer Function Documentation**

---

### 🔹 4.1 `HAL_TIM_Base_Init()`

* **Purpose**: Initializes a timer in base (counting) mode
* **Prototype**:

  ```c
  HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim);
  ```
* **Parameters**:

  * `htim`: Timer handle (e.g., `&htim2`)
* **Example**:

  ```c
  HAL_TIM_Base_Init(&htim2);
  ```
* **Expected Outcome**: Configures timer registers with prescaler, period, etc.

---

### 🔹 4.2 `HAL_TIM_Base_Start_IT()`

* **Purpose**: Starts timer and enables its interrupt
* **Prototype**:

  ```c
  HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
  ```
* **Parameters**:

  * `htim`: Timer handle
* **Example**:

  ```c
  HAL_TIM_Base_Start_IT(&htim2);
  ```
* **Expected Outcome**: Timer starts counting and triggers interrupt on overflow

---

### 🔹 4.3 `HAL_TIM_PeriodElapsedCallback()`

* **Purpose**: Callback executed when timer overflow (update event) occurs
* **Prototype**:

  ```c
  void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
  ```
* **Parameters**:

  * `htim`: Timer handle pointer (to check which timer triggered)
* **Example**:

  ```c
  void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
  {
    if (htim->Instance == TIM2)
    {
      HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Toggle LED
    }
  }
  ```
* **Expected Outcome**: Executes code every timer period (500ms here)

---

### 🔹 4.4 `__HAL_TIM_SET_COUNTER()` (Optional)

* **Purpose**: Reset or modify current timer counter
* **Prototype**:

  ```c
  __HAL_TIM_SET_COUNTER(TIM_HandleTypeDef *htim, uint32_t Counter);
  ```
* **Example**:

  ```c
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  ```
* **Outcome**: Manually resets counter (like restarting timer)

---

## **5. Example Logic Recap**

```c
HAL_TIM_Base_Start_IT(&htim2);  // Start timer interrupt

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Toggle LED every 500ms
}
```

---

## **6. Expected Outcome**

* Timer TIM2 generates update event every 500 ms
* Callback toggles LED on PA5
* Oscilloscope will show square wave if LED connected
* If logic analyzer: toggling every 500ms seen

---

## ✅ Summary Table

| Function                          | Role                              |
| --------------------------------- | --------------------------------- |
| `HAL_TIM_Base_Init()`             | Initialize base timer             |
| `HAL_TIM_Base_Start_IT()`         | Start timer with interrupt        |
| `HAL_TIM_PeriodElapsedCallback()` | Triggered on timer update         |
| `__HAL_TIM_SET_COUNTER()`         | Manually reset counter (optional) |

---

