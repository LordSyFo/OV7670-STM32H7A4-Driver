/*
 * SDExceptions.h
 *
 *  Created on: 3 Nov 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#include <Util/BaseException.h>

#ifndef INC_STORAGE_EXCEPTIONS_SDEXCEPTIONS_H_
#define INC_STORAGE_EXCEPTIONS_SDEXCEPTIONS_H_

class SDException : public BaseException {};

class MountFailure : public SDException {};

class ReadError : public SDException {};
class WriteError : public SDException {};
class OpenError : public SDException {};
class NoPathError : public SDException {};



#endif /* INC_STORAGE_EXCEPTIONS_SDEXCEPTIONS_H_ */
