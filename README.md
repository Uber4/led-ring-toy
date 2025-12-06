# Arduino LED toy with neopixel ring and arcade buttons

This project is a simple interactive toy I built for my kids as a Christmas gift, back in 2020. 
I lost the final version of the original firmware a long time ago, so I created this repository to recover it as accurately as possible, based on some backups.
It is housed inside a cardboard box and powered by an **Arduino Uno**, featuring a **24-LED Adafruit NeoPixel Ring** and **three arcade-style push buttons**.

The toy uses colors, light patterns, and basic interaction to create different engaging experiences for young children.

<p align="center">
  <img src="images/led-toy.jpg" width="350">
</p>

---

## Features

- **24-LED Adafruit NeoPixel Ring** for bright and colorful animations  
- **Three arcade machine push buttons**  
  - Each button triggers a different light pattern  
  - Designed to be easy for toddlers to press  
- **Simple menu system** that uses the three buttons to select between different animation modes  
- **Reset gesture**: pressing all three buttons at the same time resets the toy to its initial state  
- **Arduino Uno–based control logic**  
- **Durable cardboard enclosure** (simple DIY build)  
- Safe, simple, and fun for small kids

---

## How it works: operating modes

This project includes several operating modes controlled by the `modo` variable.  
Each mode changes how the NeoPixel strip behaves depending on the user's button inputs.

### Modes overview

| Mode | Name                      | Description |
|-------|--------------------------|-------------|
| **0** | **Selector**             | Navigation menu to choose the operating mode. |
| **1** | **Color mixer**          | Adjust the red, green, and blue LED values to create a custom color. |
| **2** | **Rainbow**              | Smooth rainbow animation cycling across all LEDs. |
| **3** | **Theater chase rainbow**| Theater-style chase effect combined with rainbow color cycling. |
| **4** | **Memory Mode**          | Record a color sequence by pressing R, G, or B. |

---

## Button functions by mode

### **Mode 0 — Selector**
- **R Button:** Move to the next mode (cycles through 1 → 4).
- **G Button:** Confirm the selected mode.
- One LED lights up in white to show the currently selected mode.

---

### **Mode 1 — color mixer**
Create a custom RGB color:

| Button | Action |
|--------|--------|
| **R Button** | Increase Red component (0 → 250 → reset to 0) |
| **G Button** | Increase Green component (increments of 50) |
| **B Button** | Increase Blue component (increments of 50) |

The entire LED strip updates to the combined RGB color after each button press.

---

### **Mode 2 — Rainbow**
- Displays a continuous rainbow cycle.
- Smoothly transitions all LEDs through the full color spectrum.
- Can be interrupted using the button reset combination.

---

### **Mode 3 — Theater chase rainbow**
- Produces a theater-style “moving lights” effect.
- Lights every third LED and shifts colors using the rainbow wheel.
- Repeats until the reset combo is activated.

---

### **Mode 4 — Memory mode**
Create a sequence of 24 color entries, one per LED:

| Button       | Color Assigned |
|--------------|----------------|
| **R Button** | Red (100, 0, 0) |
| **G Button** | Green (0, 100, 0) |
| **B Button** | Blue (0, 0, 100) |

- Each button press writes the corresponding color to the next LED.
- Once all 24 LEDs are filled, the strip clears and the sequence resets.

To make it easy to “start over”, there is also a **reset gesture**:

- When **all three buttons are pressed at the same time**, it returns to **mode 0**, as if the toy had just been powered on.

---

## Hardware Used

- **Arduino Uno**  
- **Adafruit NeoPixel Ring – 24 LEDs**  
- **3 × Arcade-style push buttons**  
- Resistors for button debouncing (optional depending on wiring)  
- 5V power supply (USB or external)  
- Jumper wires  
- Cardboard box (enclosure)

---