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
|:---:|---|---|:---:|
| `config.h` | `/lock/config.h` | Environment variables | [🔗](/lock/config.h) |
| `bsp.h` | `/lock/config.h` | Board support package | [🔗](/lock/bsp.h) |
| `bsp.cpp` | `/lock/config.h` | The board support package is used to store the code required for the initialisation of the board. | [🔗](/lock/bsp.cpp) |
| `event.h` | `/lock/config.h` | Event | [🔗](/lock/event.h) |
| `event.cpp` | `/lock/config.h` | Store the functions that will be called as Event. | [🔗](/lock/event.cpp) |
| `handle.h` | `/lock/config.h` | Store PW Class | [🔗](/lock/handle.h) |
| `main.h` | `/lock/main.cpp` | Main program | [🔗](/lock/main.) |
| `main.cpp` | `/lock/main.cpp` | Main program | [🔗](/lock/main.cpp) |
| `tests` | `/lock/tests` | Storing unit tests | [🔗](/lock/tests) |

### 2.1 Class

| Class | Function |
|---|---|
| `PW` | Used to control password |

## 3. License

[GNU General Public License v3.0](LICENSE)

## 4. External Link

- [Google Drive](https://drive.google.com/drive/u/2/folders/0AOCpiZtM2Mc6Uk9PVA)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

## 5. ChangeLog

- 210513 fix Usage
- 210420 init
