/*
 * I2CExceptions.h
 *
 *  Created on: 6 Oct 2020
 *      Author: SYFO
 */

#ifndef INC_SERIAL_I2CEXCEPTIONS_H_
#define INC_SERIAL_I2CEXCEPTIONS_H_

//#include <exception>
#include <Util/BaseException.h>

class I2CException : public BaseException { };

/*
 *    HAL_ERROR    = 0x01,
  	  HAL_BUSY     = 0x02,
  	  HAL_TIMEOUT  = 0x03
 * */

class UnspecifiedErrorException : public I2CException {};
class TimeoutException : public I2CException {};
class BusyException : public I2CException {};

#endif /* INC_SERIAL_I2CEXCEPTIONS_H_ */
