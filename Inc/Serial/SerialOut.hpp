/*
 * SerialOut.hpp
 *
 *  Created on: 6 Nov 2020
 *      Author: SYFO
 */

#ifndef INC_SERIAL_SERIALOUT_HPP_
#define INC_SERIAL_SERIALOUT_HPP_

#include <Serial/ISerial.h>

template<ISerial& ser>
class SerialOut {
public:
	SerialOut() = default;


	friend ostream& operator<<(const char* str);
	~SerialOut() = default;
};


#endif /* INC_SERIAL_SERIALOUT_HPP_ */
