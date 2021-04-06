/*
 * BaseException.H
 *
 *  Created on: 6 Oct 2020
 *      Author: SYFO
 */

#ifndef INC_UTIL_BASEEXCEPTION_H_
#define INC_UTIL_BASEEXCEPTION_H_


class BaseException {
public:
	BaseException() noexcept {};
	virtual ~BaseException() noexcept {};

	/** Returns a C-style character string describing the general cause
	 *  of the current error.  */
	virtual const char* what() const noexcept { return nullptr; };

};


#endif /* INC_UTIL_BASEEXCEPTION_H_ */
