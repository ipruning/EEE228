# EEE228 Lock Project

## 0. Table of Contents

- [EEE228 Lock Project](#eee228-lock-project)
  - [0. Table of Contents](#0-table-of-contents)
  - [1. Background](#1-background)
    - [1.0 Install](#10-install)
    - [1.1 Usage](#11-usage)
    - [1.2 Name Convention](#12-name-convention)
  - [2. Architecture](#2-architecture)
    - [2.0 Overall](#20-overall)
    - [2.1 Class](#21-class)
    - [2.2 Interface](#22-interface)
  - [3. License](#3-license)
  - [4. External Link](#4-external-link)
  - [5. ChangeLog](#5-changelog)

## 1. Background

### 1.0 Install

- Clone GitHub Repository `git clone https://github.com/Spehhhhh/EEE228.git`
- Switch to the directory `cd EEE228`

### 1.1 Usage

You can build the project with all supported Mbed OS build tools.

```bash
$ cd EEE228/lock
$ mbed deploy
$ mbed compile -m <TARGET> -t <TOOLCHAIN> --flash
$ mbed compile -m KL46Z -t GCC_ARM
```

### 1.2 Name Convention

- Class Naming Convention: `CapWords`
- Class Member Convention: `lower_with_under_`
- Function Naming Convention: `CapWords()`
- Variables Naming Convention: `lower_with_under`

## 2. Architecture

### 2.0 Overall

| Module | Location | Function | Location |
|:---|:---|:---|:---:|
| `config.h` | `/lock/config.h` | Environment variables | [🔗](/lock/config.h) |
| `bsp.h` | `/lock/bsp.h` | Board support package | [🔗](/lock/bsp.h) |
| `bsp.cpp` | `/lock/bsp.cpp` | The board support package is used to store the code required for the initialisation of the board. | [🔗](/lock/bsp.cpp) |
| `event.h` | `/lock/event.h` | Event | [🔗](/lock/event.h) |
| `event.cpp` | `/lock/event.cpp` | Store the functions that will be called as Event. | [🔗](/lock/event.cpp) |
| `handle.h` | `/lock/handle.h` | Store PW Class | [🔗](/lock/handle.h) |
| `main.h` | `/lock/main.h` | Main program | [🔗](/lock/main.h) |
| `main.cpp` | `/lock/main.cpp` | Main program | [🔗](/lock/main.cpp) |
| `tests` | `/lock/tests` | Storing unit tests | [🔗](/lock/tests) |
| `drivers` | `/lock/drivers` | Storing all drivers | [🔗](/lock/drivers) |

### 2.1 Class

| Class | Function |
|---|---|
| `PW` | Used to control password |

### 2.2 Interface

| Peripheral            | Interface | Type       |
| --------------------- | --------- | ---------- |
| Relay control         | PTA0      | Digital IO |
| Buzzer control        | PTA6      | PWM        |
| Exit button green LED | PTA13     | Digital IO |
| Exit button red LED   | PTA14     | Digital IO |
| Exit button COM_TX    | PTE1      | USART1     |
| Exit button COM_RX    | PTE0      | USART1     |
| ESP8266 COM_TX        | PTE23     | USART2     |
| ESP8266 COM_RX        | PTE22     | USART2     |
| Keypad Micro D6       | PTA12     | Digital IO |
| Keypad Micro D5       | PTA4      | Digital IO |
| Keypad Micro D4       | PTA5      | Digital IO |
| Keypad Micro D3       | PTC8      | Digital IO |
| Keypad Micro D2       | PTD3      | Digital IO |
| Keypad Micro D1       | PTA2      | Digital IO |
| Keypad Micro D0       | PTA1      | Digital IO |
| LCD_P40               | PTD0      | Digital IO |
| LCD_P52               | PTE4      | Digital IO |
| LCD_P19               | PTB23     | Digital IO |
| LCD_P18               | PTB22     | Digital IO |
| LCD_P37               | PTC17     | Digital IO |
| LCD_P17               | PTB21     | Digital IO |
| LCD_P7                | PTB7      | Digital IO |
| LCD_P8                | PTB8      | Digital IO |
| LCD_P53               | PTE5      | Digital IO |
| LCD_P38               | PTC18     | Digital IO |
| LCD_P10               | PTB10     | Digital IO |
| LCD_P11               | PTB11     | Digital IO |

## 3. License

[GNU General Public License v3.0](LICENSE)

## 4. External Link

- [Google Drive](https://drive.google.com/drive/u/2/folders/0AOCpiZtM2Mc6Uk9PVA)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

## 5. ChangeLog

- 210513 fix Usage
- 210420 init
