/*
 * SCCB.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: SYFO
 */

#include <Serial/I2C.h>
#include "stm32h7xx_hal.h"
#include <cassert>

#define I2C_DELAY	1000

namespace Serial {

I2C::I2C(I2C_HandleTypeDef* handle) : busHandle_(handle) {
}

I2C::~I2C() {
	// TODO Auto-generated destructor stub
}

/*
 * Write data over the I2C-bus.
 *
 * Use this method to write data over the I2C-bus.
 *
 * @param ´addr´ 	Device address for which the data should be written to.
 * @param ´data´ 	Data to be transmitted.
 * @param ´count´	The number of bytes to transmit.
 * */
void I2C::Write(const uint16_t addr, const uint8_t* reg_and_data, const uint16_t count)
{
	// TODO: Force for testing!
	HAL_StatusTypeDef status;
	status = HAL_I2C_Master_Transmit(busHandle_, addr, const_cast<uint8_t*>(reg_and_data), count, I2C_DELAY);

	if (status!=HAL_OK)
		HandleError(status);

}

/*
 * Write data to a specific register over the I2C-bus.
 *
 * Use this method to write data to a specific register over the I2C-bus.
 *
 * @param ´addr´ 	Device address for which the data should be written to.
 * @param ´reg´		Register address
 * @param ´data´ 	Data to be transmitted.
 * @param ´count´	The number of bytes to transmit.
 * */
void I2C::WriteToReg(const uint8_t addr, const uint8_t reg, const uint8_t* data, const uint16_t dataCount)
{
	HAL_StatusTypeDef status = HAL_ERROR;

	status = HAL_I2C_Mem_Write(busHandle_, addr, reg, 1, const_cast<uint8_t*>(data), dataCount, I2C_DELAY);

	if (status!=HAL_OK){
		if (status==HAL_TIMEOUT)
			throw TimeoutException();
		else if (status==HAL_BUSY)
			throw BusyException();
		else
			throw UnspecifiedErrorException();
	}
}

void I2C::HandleError(HAL_StatusTypeDef status)
{
	if (status==HAL_TIMEOUT)
		throw TimeoutException();
	else if (status==HAL_BUSY)
		throw BusyException();
	else
		throw UnspecifiedErrorException();
}

/*
 * Read data from a specific register over the I2C-bus.
 *
 * Use this method to read data from a specific register over the I2C-bus.
 *
 * @param ´addr´ 	Device address for which the data should be read from.
 * @param ´reg´		Register address
 * @param ´data´ 	Data container for the read data.
 * @param ´count´	The maximum bytes to read.
 * */
void I2C::ReadFromReg(const uint8_t addr, const uint8_t reg, uint8_t* data, const uint16_t dataCount)
{
	HAL_StatusTypeDef status = HAL_ERROR;

	// TODO: Add timeout!
	status = HAL_I2C_Master_Receive(busHandle_, addr, data, dataCount, I2C_DELAY);

	if (status!=HAL_OK)
		HandleError(status);

}

void dummyTXHandler(I2C_HandleTypeDef* handle){
	volatile int x = 0;
}

/*
 * Read data over the I2C-bus.
 *
 * Use this method to read data from I2C-bus.
 *
 * @param ´addr´ 	Device address for which the data should be read from.
 * @param ´data´ 	Data container for the read data.
 * @param ´count´	The maximum bytes to read.
 * */
void I2C::Read(const uint16_t addr, uint8_t* data, const uint16_t count)
{
	HAL_StatusTypeDef status;
	status = HAL_I2C_Master_Receive(busHandle_, addr, data, count, I2C_DELAY);

	if (status!=HAL_OK)
		HandleError(status);

}



} /* namespace Serial */
