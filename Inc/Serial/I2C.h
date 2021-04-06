/*
 * SCCB.h
 *
 *  Created on: Sep 15, 2020
 *      Author: SYFO
 */

#ifndef INC_SERIAL_I2C_H_
#define INC_SERIAL_I2C_H_

#include "ISerial.h"
#include "stm32h7xx_hal.h"
#include "I2CExceptions.h"

namespace Serial {

class I2C : public ISerial {
public:
	I2C(I2C_HandleTypeDef* handle);

	void Write(const uint16_t addr, const uint8_t* data, const uint16_t count);

	void Read(const uint16_t addr, uint8_t* data, const uint16_t count);

	void WriteToReg(const uint8_t addr, const uint8_t reg, const uint8_t* data, const uint16_t count);

	void ReadFromReg(const uint8_t addr, const uint8_t reg, uint8_t* data, const uint16_t count);

	virtual ~I2C();

private:

	void HandleError(HAL_StatusTypeDef status);

	I2C_HandleTypeDef* busHandle_;

};

} /* namespace Serial */

#endif /* INC_SERIAL_I2C_H_ */
