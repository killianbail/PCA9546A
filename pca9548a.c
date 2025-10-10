// 
// STM32 driver for I2C multiplexers TCA9548A and PCA9548A
//
// Copyright (c) 2023 Jonathan Tainer. Subject to the BSD 2-Clause License.
//

#include <stdio.h>
#include <cmsis_os2.h>
#include "i2c.h"
#include "tca9548.h"
#include "utils.h"

static uint8_t currentChannelMask = 0xFF;

void i2c_mux_reset(i2c_mux_t* mux) {
	if (mux->rst_port == NULL || mux->rst_pin == 0)
	  printf("I2C mux error.\n");
	
	// Pull reset pin low
	HAL_GPIO_WritePin(mux->rst_port, mux->rst_pin, GPIO_PIN_RESET);
	osDelay(SECONDS_TO_TICKS(0.001));

	// Bring multiplexer out of reset
	HAL_GPIO_WritePin(mux->rst_port, mux->rst_pin, GPIO_PIN_SET);
	osDelay(SECONDS_TO_TICKS(0.001));

	// Ensure all channels are disabled by default
	i2c_mux_select_multi(mux, 0);
}

void i2c_mux_select(i2c_mux_t* mux, int ch) {
	uint8_t mask = 1 << ch;
	i2c_mux_select_multi(mux, mask);
}

void i2c_mux_select_multi(i2c_mux_t* mux, uint8_t mask) {
	if(mux->hi2c == NULL)
		printf("Error, I2C mux channel handle not set.");
	if(currentChannelMask == mask)
		return;

	// Transmit bitmask to multiplexer
	uint8_t addr = (I2C_MUX_BASE_ADDR + mux->addr_offset) << 1;
	i2c_rtos_lock(mux->hi2c);
	i2c_rtos_transmit(mux->hi2c, addr, &mask, 1);

	// Read back bitmask from multiplexer to verify
	uint8_t mask_check = 0;
	i2c_rtos_receive(mux->hi2c, addr, &mask_check, 1);
	i2c_rtos_unlock(mux->hi2c);
	osDelay(SECONDS_TO_TICKS(0.001)); // Ensure mux has switched
}
