/**
 * @file pca9546a_platform.h
 * @author Killian Baillifard
 * @date 31.10.2025
 * @brief PCA9546A platform interface.
 */

 
#ifndef PCA9546A_PLATFORM_H
#define PCA9546A_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Platform-specific sleep function.
 * @param seconds Time to sleep in seconds.
 */
void pca9548a_sleep(float seconds);

/**
 * @brief Platform-specific GPIO write function for the reset pin.
 * @param address I2C address of the PCA9546A, allow to differentiate different devices.
 * @param state Desired state of the reset pin (true for HIGH, false for LOW).
 */
void pca9548a_gpio_write_reset_pin(uint8_t address, bool state);

/**
 * @brief Platform-specific I2C read function.
 * @param address I2C address of the PCA9546A.
 * @return The byte read from the device.
 */
uint8_t pca9548a_i2c_read(uint8_t address);

/**
 * @brief Platform-specific I2C write function.
 * @param address I2C address of the PCA9546A.
 * @param byte The byte to write to the device.
 */
void pca9548a_i2c_write(uint8_t address, uint8_t byte);

#ifdef __cplusplus
}
#endif

#endif // PCA9546A_PLATFORM_H
