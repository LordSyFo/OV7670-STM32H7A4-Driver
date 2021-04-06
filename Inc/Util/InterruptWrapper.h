/*
 * InterruptWrapper.h
 *
 *  Created on: Sep 23, 2020
 *      Author: SYFO
 */

#ifndef INC_UTIL_INTERRUPTWRAPPER_H_
#define INC_UTIL_INTERRUPTWRAPPER_H_

#include <stdint.h>
#include <Util/Interruptable.h>

namespace Util {

typedef void (*CallbackFunction)(uint16_t pin);

class InterruptWrapper {
public:

	InterruptWrapper() : callback_(nullptr), object_(nullptr) {}
	//InterruptWrapper(CallbackFunction* callback) : callback_(CallbackFunction), object_(nullptr) {}	NOT USED

	bool ConnectCallback(CallbackFunction function)
	{
		if (function != nullptr)
			callback_ = function;

		return function != nullptr;
	}

	bool ConnectInterruptableCallback(Interruptable* object)
	{
		if (object != nullptr)
			object_ = object;

		return object != nullptr;
	}

	void Callback(uint16_t pin){
		if (object_)
			object_->OnInterrupt(pin);

		// TODO: Make sure that it is an intended use that we can attach both a static method and object!
		if (callback_)
			(*callback_)(pin);
	}

	virtual ~InterruptWrapper() {}

private:
	CallbackFunction callback_;
	Interruptable* object_;

};

} /* namespace Util */

#endif /* INC_UTIL_INTERRUPTWRAPPER_H_ */
