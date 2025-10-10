/**
 * @file pca9546a.c
 * @author Killian Baillifard
 * @date 10.10.2025
 * @brief PCA9546A implementation for the STM32WB5MXX plateform.
 * @copyright Copyright (c) 2023 Jonathan Tainer. Subject to the BSD 2-Clause License.
 */

// Includes

#include <cmsis_os2.h>
#include "pca9546a.h"
#include "i2c.h"
#include "utils.h"

// Static variables

static uint8_t currentMask = ~PCA9546A_VALID_CHANNELS_MASK;

// Definitions

void pca9548a_reset(Pca9546a *mux) {

	// Pull down and up the reset pin
	HAL_GPIO_WritePin(mux->rst_port, mux->rst_pin, GPIO_PIN_RESET);
	osDelay(SECONDS_TO_TICKS(PCA9546A_RESET_DELAY_SECONDS));
	HAL_GPIO_WritePin(mux->rst_port, mux->rst_pin, GPIO_PIN_SET);
	osDelay(SECONDS_TO_TICKS(PCA9546A_RESET_DELAY_SECONDS));
	pca9548a_set_selected_channels(mux, 0);
}

void pca9548a_select_single_channel(Pca9546a *mux, uint8_t channel) {

	// If channel is out of range, do nothing
	if(channel >= PCA9546A_NUMBER_OF_CHANNELS)
		return;

	// Enable only selected channel
	pca9548a_set_selected_channels(mux, 1 << channel);
}

void pca9548a_set_selected_channels(Pca9546a *mux, uint8_t mask) {

	// Memorize last set channel, avoid unnecessary writes
	mask &= PCA9546A_VALID_CHANNELS_MASK;
	if(mask == currentMask)
		return;
	currentMask = mask;

	// Apply new mask
	i2c_lock(mux->hi2c);
	i2c_write(mux->hi2c, mux->address, &currentMask, 1);
	i2c_unlock(mux->hi2c);
}

uint8_t pca9546a_get_selected_channels(Pca9546a *mux) {

	// Read and update current channel mask
	i2c_lock(mux->hi2c);
	i2c_read(mux->hi2c, mux->address, &currentMask, 1);
	i2c_unlock(mux->hi2c);
	currentMask &= PCA9546A_VALID_CHANNELS_MASK;
	return currentMask;
}
