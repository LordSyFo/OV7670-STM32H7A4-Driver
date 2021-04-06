/*
 * SPIExceptions.h
 *
 *  Created on: Oct 8, 2020
 *      Author: SYFO
 */

#ifndef INC_SERIAL_SPIEXCEPTIONS_H_
#define INC_SERIAL_SPIEXCEPTIONS_H_

#include <Util/BaseException.h>

class SPIException : public BaseException { };

class AsyncReceptionError : public SPIException {};
class AsyncTransmissionError : public SPIException {};
class TimeoutError : public SPIException {};



#endif /* INC_SERIAL_SPIEXCEPTIONS_H_ */
