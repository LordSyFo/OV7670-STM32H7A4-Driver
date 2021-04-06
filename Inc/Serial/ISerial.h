/*
 * ISerial.h
 *
 *  Created on: Sep 15, 2020
 *      Author: SYFO
 */

#ifndef INC_SERIAL_ISERIAL_H_
#define INC_SERIAL_ISERIAL_H_

#include <stdint.h>

namespace Serial {

class ISerial {
public:
	ISerial();

	/*
	 * Write data over a serial bus.
	 *
	 * Use this method to write data over the bus.
	 *
	 * @param ´addr´ 	Device address for which the data should be written to. Ignored when the serial interface has no addressing scheme.
	 * @param ´data´ 	Data to be transmitted.
	 * @param ´count´	The number of bytes to transmit.
	 * */
	virtual void Write(const uint16_t addr, const uint8_t* data, const uint16_t count) = 0;

	/*
	 * Read data over a serial bus.
	 *
	 * Use this method to read data from the bus.
	 *
	 * @param ´addr´ 	Device address for which the data should be read from. Ignored when the serial interface has no addressing scheme.
	 * @param ´data´ 	Data container for the read data.
	 * @param ´count´	The maximum bytes to read.
	 * */
	virtual void Read(const uint16_t addr, uint8_t* data, const uint16_t count) = 0;

	virtual ~ISerial();
};

} /* namespace Serial */

#endif /* INC_SERIAL_ISERIAL_H_ */
