# PCA9546A Library

## Overview

This library provides a high level multiplatform C interface for Texas Instruments **PCA9546A** I2C multiplexer.

## Usage

Two functions in [pca9546a.h](./include/pca9546a.h) allow to set the selection of the multiplexer :
- `pca9546a_select_single_channel` to select one channel.
- `pca9546a_set_selected_channels` to select multiple channels using a mask.

## Platform

To work with this library, 1 files must be implemented :

- `pca9546a_platform.c` which contains the implementations of the platform functions defined in [pca9546a_platform.h](./include/pca9546a_platform.h).

```c
#include <my_mcu_defs.h>
#include "pca9546a_platform.h"

void pca9548a_sleep(float seconds) {
    my_mcu_sleep(seconds);
}

void pca9548a_gpio_write_reset_pin(uint8_t address, bool state) {
    if(address != PCA9546A_ADDR_BASE)
        return;
    if(state)
        my_mcu_pin_write(port, pin);
    else
        my_mcu_pin_write(port, pin);
}

uint8_t pca9548a_i2c_read(uint8_t address) {
    uint8_t byte;
    my_mcu_i2c_read(address, &byte);
    return byte;
}

void pca9548a_i2c_write(uint8_t address, uint8_t byte) {
    my_mcu_i2c_write(address, &byte);
}
```

## Credits

- Jonathan Trainer, original creator.
- Killian Baillifard, current reworked version.
