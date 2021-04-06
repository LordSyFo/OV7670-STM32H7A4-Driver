/*
 * Interruptable.h
 *
 *  Created on: Sep 23, 2020
 *      Author: SYFO
 */

#ifndef INC_UTIL_INTERRUPTABLE_H_
#define INC_UTIL_INTERRUPTABLE_H_

namespace Util {

class Interruptable {
public:
	Interruptable(){}

	virtual void OnInterrupt(uint16_t pin) = 0;

	virtual ~Interruptable(){}
};

} /* namespace Util */

#endif /* INC_UTIL_INTERRUPTABLE_H_ */
