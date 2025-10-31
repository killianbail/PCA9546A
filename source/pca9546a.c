/**
 * @file pca9546a.c
 * @author Killian Baillifard
 * @date 10.10.2025
 * @brief PCA9546A implementation.
 */

// Includes

#include "pca9546a.h"
#include "pca9546a_platform.h"

// Implementations

void pca9546a_reset(Pca9546a *mux) {

	// Pull down and up the reset pin
	pca9548a_gpio_write_reset_pin(mux->address, false);
	pca9548a_sleep(PCA9546A_RESET_DELAY_SECONDS);
	pca9548a_gpio_write_reset_pin(mux->address, true);
	pca9548a_sleep(PCA9546A_RESET_DELAY_SECONDS);
	pca9546a_set_selected_channels(mux, 0);
}

void pca9546a_select_single_channel(Pca9546a *mux, uint8_t channel) {

	// If channel is out of range, do nothing
	if(channel >= PCA9546A_NUMBER_OF_CHANNELS)
		return;

	// Enable only selected channel
	pca9546a_set_selected_channels(mux, 1 << channel);
}

void pca9546a_set_selected_channels(Pca9546a *mux, uint8_t mask) {

	// Memorize last set channel, avoid unnecessary writes
	mask &= PCA9546A_VALID_CHANNELS_MASK;
	if(mask == mux->currentMask)
		return;

	// Apply new mask
	mux->currentMask = mask;
	pca9548a_i2c_write(mux->address, mux->currentMask);
}

uint8_t pca9546a_get_selected_channels(Pca9546a *mux) {

	// Read and update current channel mask
	mux->currentMask = pca9548a_i2c_read(mux->address);
	mux->currentMask &= PCA9546A_VALID_CHANNELS_MASK;
	return mux->currentMask;
}
