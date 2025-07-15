# 📘 HAL Function Documentation – Digital Input (Button Control LED)

---

## **1. Introduction**

This guide demonstrates how to use a push button as a **digital input** on the STM32F103C8T6 (Blue Pill) using the HAL library. When the button is pressed, an LED connected to PC13 will turn ON.

---

## **2. What is Digital Input?**

Digital input allows microcontrollers to detect logical HIGH or LOW states from external sources like buttons, sensors, or switches.

---

## **3. Development Setup**

| Component  | Description                            |
| ---------- | -------------------------------------- |
| MCU        | STM32F103C8T6 (Blue Pill)              |
| IDE        | STM32CubeIDE                           |
| Library    | STM32 HAL (Hardware Abstraction Layer) |
| Input Pin  | PA0 (Button)                           |
| Output Pin | PC13 (On-board LED)                    |

---

## **4. HAL Function Reference**

---

### 🔹 **4.1 `HAL_GPIO_Init()`**

* **Purpose**: Initializes both input and output GPIO pins.
* **Prototype**:

  ```c
  void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
  ```
* **Parameters**:

  * `GPIOx`: GPIO port (e.g., GPIOA, GPIOC)
  * `GPIO_Init`: Pointer to `GPIO_InitTypeDef` structure
* **Example**:

  ```c
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  ```
* **Expected Outcome**: Configures PA0 as a floating input pin.

---

### 🔹 **4.2 `HAL_GPIO_ReadPin()`**

* **Purpose**: Reads the logic level of a GPIO input pin.
* **Prototype**:

  ```c
  GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
  ```
* **Parameters**:

  * `GPIOx`: GPIO port
  * `GPIO_Pin`: Pin number to read
* **Example**:

  ```c
  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // LED ON
  }
  ```
* **Expected Outcome**: Reads PA0; if HIGH, turns ON LED.

---

### 🔹 **4.3 `HAL_GPIO_WritePin()`**

* **Purpose**: Controls the LED output pin.
* **Prototype**:

  ```c
  void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
  ```
* **Example**:

  ```c
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET); // LED OFF
  ```
* **Expected Outcome**: Sets PC13 HIGH (turns OFF active-low LED).

---

## **5. Example Program Summary**

```c
if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
{
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // LED ON
}
else
{
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);   // LED OFF
}
```

---

## **6. Expected Output**

* When the button connected to PA0 is pressed, LED on PC13 turns ON.
* When the button is released, LED turns OFF.
* HAL handles all low-level register control.

