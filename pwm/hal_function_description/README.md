---

# Beginner’s Guide to STM32F103C8T6 – PWM with HAL Library

---

## **1. Introduction**

PWM (Pulse Width Modulation) allows us to control things like motor speed, LED brightness, or signal generation by toggling a pin at a fixed frequency but with variable ON time (duty cycle).

STM32 has multiple timers that support PWM using Output Compare channels.

---

## **2. What is PWM?**

PWM is a technique where a digital signal is toggled ON/OFF at high frequency. The ratio of ON time to the full cycle time is called **duty cycle**.

Example:

* 50% duty cycle → ON for 50% of the time
* 100% → always ON
* 0% → always OFF

---

## **3. Development Setup**

| Component | Value                      |
| --------- | -------------------------- |
| MCU       | STM32F103C8T6 (Blue Pill)  |
| IDE       | STM32CubeIDE               |
| Library   | STM32 HAL                  |
| Timer     | TIM1 (or TIM2, TIM3, etc.) |
| PWM Pin   | PA8 (TIM1 Channel 1)       |

---

## **4. HAL PWM Function Documentation**

---

### 🔹 4.1 `HAL_TIM_PWM_Init()`

* **Purpose**: Initializes timer in PWM mode
* **Prototype**:

  ```c
  HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim);
  ```
* **Parameters**:

  * `htim`: pointer to timer handle
* **Example**:

  ```c
  HAL_TIM_PWM_Init(&htim1);
  ```
* **Outcome**: Configures base timer registers to generate PWM-compatible output.

---

### 🔹 4.2 `HAL_TIM_PWM_ConfigChannel()`

* **Purpose**: Sets channel to output PWM with chosen duty and polarity
* **Prototype**:

  ```c
  HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(
      TIM_HandleTypeDef *htim,
      TIM_OC_InitTypeDef *sConfig,
      uint32_t Channel);
  ```
* **Parameters**:

  * `htim`: timer handle
  * `sConfig`: output compare config
  * `Channel`: TIM\_CHANNEL\_1, 2, 3, etc.
* **Example**:

  ```c
  TIM_OC_InitTypeDef sConfig = {0};
  sConfig.OCMode = TIM_OCMODE_PWM1;
  sConfig.Pulse = 500; // 50% of 1000
  sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfig.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfig, TIM_CHANNEL_1);
  ```
* **Outcome**: Configures PA8 to generate PWM with 50% duty.

---

### 🔹 4.3 `HAL_TIM_PWM_Start()`

* **Purpose**: Starts the PWM signal on the chosen channel
* **Prototype**:

  ```c
  HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
  ```
* **Parameters**:

  * `htim`: timer handle
  * `Channel`: TIM\_CHANNEL\_1, etc.
* **Example**:

  ```c
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  ```
* **Outcome**: Begins toggling the output pin with configured duty and frequency.

---

### 🔹 4.4 `__HAL_TIM_SET_COMPARE()`

* **Purpose**: Dynamically updates the duty cycle during runtime
* **Prototype**:

  ```c
  __HAL_TIM_SET_COMPARE(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t Compare);
  ```
* **Parameters**:

  * `htim`: timer handle
  * `Channel`: PWM output channel
  * `Compare`: new pulse value (duty cycle)
* **Example**:

  ```c
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 750); // 75% duty
  ```
* **Outcome**: Changes PWM ON-time (brightness, speed, etc.)

---

## **5. Example Program Logic (Application Layer)**

```c
// Inside while(1) loop:
for (uint16_t duty = 0; duty <= 1000; duty += 50)
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty);
    HAL_Delay(50);
}
for (uint16_t duty = 1000; duty > 0; duty -= 50)
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty);
    HAL_Delay(50);
}
```

* 1000 = full PWM period (based on timer config)
* This smoothly increases/decreases brightness or motor speed

---

## **6. Expected Outcome**

* PWM output is generated on PA8 (TIM1\_CH1)
* Duty cycle increases/decreases smoothly
* On oscilloscope, you will see square wave with variable ON time
* If connected to LED: brightness will fade in/out

---

## ✅ Summary Table

| Function                      | Role                               |
| ----------------------------- | ---------------------------------- |
| `HAL_TIM_PWM_Init()`          | Init timer in PWM mode             |
| `HAL_TIM_PWM_ConfigChannel()` | Configure channel pulse + polarity |
| `HAL_TIM_PWM_Start()`         | Enable PWM output                  |
| `__HAL_TIM_SET_COMPARE()`     | Adjust duty cycle dynamically      |

---

