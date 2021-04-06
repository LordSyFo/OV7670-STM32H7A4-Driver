/*
 * Thread.hpp
 *
 *  Created on: Oct 28, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_THREAD_THREAD_HPP_
#define INC_THREAD_THREAD_HPP_

#include "cmsis_os.h"
#include <Thread/Events/Events.hpp>
#include <Thread/Mutex.hpp>

namespace Thread {

inline void Initialize()
{
	Events::Init();
	Mutex::Init();
}

inline osThreadId_t CreateThread(osThreadFunc_t func, void *argument ,const char* name, osPriority_t priority = osPriorityNormal) {

	/* Creation of ESP32 Comm thread */
	osThreadAttr_t threadAttributes;
	threadAttributes.name = name;
	threadAttributes.attr_bits = osThreadDetached;
	threadAttributes.cb_mem = NULL;
	threadAttributes.cb_size = 0;
	threadAttributes.stack_mem = NULL;
	threadAttributes.stack_size = 128 * 128;
	threadAttributes.priority = priority;
	threadAttributes.tz_module = 0;

	osThreadId_t tmpThread;

	tmpThread = osThreadNew(func, argument, &threadAttributes);
	if (tmpThread == NULL) assert(false);
	return tmpThread;
}

}



#endif /* INC_THREAD_THREAD_HPP_ */
