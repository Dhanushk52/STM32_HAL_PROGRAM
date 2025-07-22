---

#### 📝 Guide: Program STM32F103C8 (Blue Pill) via USB DFU using CubeProgrammer

### 🔧 Prerequisites:

* STM32F103C8T6 Blue Pill
* USB cable
* STM32CubeProgrammer installed
* generic_boot20_pc13.bin DFU bootloader (Maple DFU) is in this path (USB_DFU_GUIDE/Bootloader_file/generic_boot20_pc13.bin)
* (Optional) Zadig for Windows DFU driver

---

### ⏱️ Step-by-Step Walkthrough:

#### **Step 1 – Flash USB DFU Bootloader**

*(Via ST-Link or UART if already available)*

1. Set **BOOT0 = 1**, **BOOT1 = 0**, then reset the MCU.
2. Open **STM32CubeProgrammer**.
3. Choose **“ST-LINK”** (or USART) for the connection.
4. Load **`generic_boot20_pc13.bin`** – address **0x08000000**.
5. Click **Start Programming**.
6. After flashing, set **BOOT0 = 0** and reset.

---

#### **Step 2 – Prepare DFU Environment**

1. Connect the Blue Pill to your PC via USB.
2. On Windows, check **Device Manager**.

   * If “STM32 BOOTLOADER” appears with warning, install **WinUSB** using **Zadig**.
3. Reconnect USB – device should enumerate properly.

---

#### **Step 3 – Flash Firmware via USB**

1. Launch **STM32CubeProgrammer**.
2. Select the **USB interface** and click **Connect**.
3. Load your application `.hex` or `.bin`; set start address `0x08000000`.
4. Click **Download** (or **Start Programming**).
5. Once complete, reset the board with **BOOT0 = 0**.
6. Your new firmware runs directly via USB DFU—no FTDI or ST-Link needed.

---

### ✅ Summary:

| Scenario                 | Connection Type | Bootloader | App Flow via USB                   |
| ------------------------ | --------------- | ---------- | ---------------------------------- |
| First flashing           | ST‑LINK or UART | Flash DFU  | –                                  |
| Normal programming after | USB DFU         | Active     | USB → CubeProgrammer → Flash → Run |

---

### 🎯 Pro Tips:

* Ensure PA11/PA12 wiring + 1.5 kΩ from PA12 to 3.3 V.
* Use `.hex` or `.bin` from STM32CubeIDE build.
* Reset with BOOT0 = 0 to boot into your application.

---

