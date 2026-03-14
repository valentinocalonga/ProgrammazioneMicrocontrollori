# 📟 Microcontroller Programming 
(SUPSI - BSc Computer Engineering 👨🏻‍💻)  

## 🚧 Project Status ![WIP](https://img.shields.io/badge/WIP-in%20progress-yellow)![Learning](https://img.shields.io/badge/project-learning-blue)

This project is currently under development and used for learning purposes.
Features and architecture may change over time.

![Language](https://img.shields.io/badge/language-C99-blue)
![Platform](https://img.shields.io/badge/platform-PIC32MX-green)
![Toolchain](https://img.shields.io/badge/compiler-XC32-orange)
![IDE](https://img.shields.io/badge/IDE-MPLAB%20X-lightgrey)
![Status](https://img.shields.io/badge/status-educational%20project-yellow)

Embedded firmware project for **PIC32MX370F512L** implementing:

- UART serial command interface  
- GPIO driver abstraction  
- LED control logic  
- Switch input handling  
- Modular embedded architecture
- ...more!

Developed for the **Microcontroller Programming course (SUPSI)**.

---

## ✨ Overview

The firmware allows controlling onboard LEDs through:
- **serial commands sent via UART4**
- **acting on on-board switches**
- or **without user interaction**.

It demonstrates:

- direct register programming  
- peripheral configuration  
- embedded modular driver design  
- simple command parsing  
- hardware abstraction techniques  

---

## 🧱 Project Structure

```
.
├── main.c
├── GPIO.c
├── GPIO.h
├── Leds.c
├── Leds.h
├── Uart.c
├── Uart.h
├── EasterEgg.c
├── EasterEgg.h
```

---

## 🔹 GPIO Driver

Responsible for:

- LED pin configuration  
- switch input configuration  
- direct port manipulation  

Key functions:

```c
void initLeds(void);
void initSwitches(void);
int readSwitch(int sw);
void toggleLed(int led);
```

---

## 🔹 LED Abstraction Layer

Provides high-level LED control independent from hardware registers.

```c
void setLed(int ledNumber, int state);
```

---

## 🔹 UART Driver

Polling-based UART4 driver.

Features:

- character transmission  
- string transmission  
- command reception  

```c
void initUART(unsigned int baud);
void putU4(int c);
void putU4_string(char* str);
char getU4(void);
char* getString(void);
```

---

## 🔹 Easter Egg Module

Contains demo routines for exercises and testing.

```c
void easter01(void);
```

---

## ⚙️ Hardware Target

| Parameter | Value |
|-----------|------|
| MCU | PIC32MX370F512L |
| SYSCLK | ~80 MHz |
| PBCLK | ~20 MHz |
| UART | UART4 |
| Default baudrate | 9600 |

---

## 🔌 Pin Mapping

### LEDs

| LED | Port |
|-----|------|
| LED0 | RA0 |
| LED1 | RA1 |
| LED2 | RA2 |
| LED3 | RA3 |
| LED4 | RA4 |
| LED5 | RA5 |
| LED6 | RA6 |
| LED7 | RA7 |

### Switches

| Switch | Pin |
|--------|-----|
| SW0 | RF3 |
| SW1 | RF5 |
| SW2 | RF4 |
| SW3 | RD15 |
| SW4 | RD14 |
| SW5 | RB11 |
| SW6 | RB10 |
| SW7 | RB9 |

---

## 💬 Example Serial Commands

Using a serial terminal (SerialTools, PuTTY, TeraTerm):

```
LED1 ON
LED2 OFF
LED7 ON
```

The firmware parses received commands and updates LED states.

---

## 🛠️ Build & Flash

### Requirements

- MPLAB X IDE  
- XC32 Compiler  
- PIC32MX370F512L microcontroller + board  

### Steps

```
1. Open project in MPLAB X
2. Select device PIC32MX370F512L
3. Clean and Build project
4. Flash firmware to board

NOTE: There are different methods available in the main function. Decomment the one you want to use, comment the others.
```

---

## 🎓 Educational Goals

This project demonstrates:

- bare-metal peripheral configuration  
- register-level embedded programming  
- modular firmware design  
- UART communication basics  
- polling architecture  

---

## 👨‍💻 Author

**Valentino Calonga**  
BSc Computer Engineering – SUPSI  
