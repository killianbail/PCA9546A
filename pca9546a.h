/**
 * @file pca9546a.h
 * @author Killian Baillifard
 * @date 10.10.2025
 * @brief PCA9546A interface for the STM32WB5MXX plateform.
 * @copyright Copyright (c) 2023 Jonathan Tainer. Subject to the BSD 2-Clause License.
 */

#ifndef PCA9546A_H
#define PCA9546A_H

#ifdef __cplusplus
extern "C" {
#endif

// Includes

#include <stm32wb5mxx.h>
#include <stm32wbxx_hal.h>

// Address definitions

#define PCA9546A_ADDR_BASE 					0b11100000
#define PCA9546A_ADDR_A2_MASK				0b00001000
#define PCA9546A_ADDR_A1_MASK				0b00000100
#define PCA9546A_ADDR_A0_MASK				0b00000010

// Constants

#define PCA9546A_NUMBER_OF_CHANNELS			4
#define PCA9546A_RESET_DELAY_SECONDS		0.001f
#define PCA9546A_VALID_CHANNELS_MASK		0b00001111

// Multiplexer structure

/**
 * @brief PCA9546A structure.
 */
typedef struct Pca9546a {
	I2C_HandleTypeDef *hi2c;
	uint8_t address;
	GPIO_TypeDef *resetPort;
	uint16_t resetPin;
	uint8_t currentMask;
} Pca9546a;

// Functions prototypes

/**
 * @brief Perform hard reset through reset pin.
 * @param mux Handle to the PCA9548A structure.
 */
void pca9546a_reset(Pca9546a *mux);

/**
 * @brief Select the given channel.
 * @param mux Handle to the PCA9548A structure.
 * @param channel Channel number between 0 and 3. Do nothing if value is out of bounds.
 */
void pca9546a_select_single_channel(Pca9546a *mux, uint8_t channel);

/**
 * @brief Select channels according to the given mask.
 * @param mux Handle to the PCA9548A structure.
 * @param mask Bits 0 to 3 sets the channels which will be enabled. Bits 4 to 7 are ignored.
 */
void pca9546a_set_selected_channels(Pca9546a *mux, uint8_t mask);

/**
 * Read selected channels.
 * @param mux Handle to the PCA9548A structure.
 * @return Bitmask of selected channels, on bits 0 to 3.
 */
uint8_t pca9546a_get_selected_channels(Pca9546a *mux);

#ifdef __cplusplus
}
#endif

#endif // PCA9546A_H
