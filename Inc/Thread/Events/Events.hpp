/*
 * Events.hpp
 *
 *  Created on: Oct 25, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_EVENTS_EVENTS_HPP_
#define INC_EVENTS_EVENTS_HPP_

#include <stdint.h>
#include <assert.h>
#include "cmsis_os.h"

namespace Thread {
namespace Events {

extern osSemaphoreId_t SPISelectEvent;
extern osSemaphoreId_t DCMIFrameCaptureEvent;
constexpr uint32_t k_MaxTimeout = osWaitForever;

// Timeout in ms
inline osStatus_t Wait(osSemaphoreId_t event, uint32_t timeout = k_MaxTimeout){
	if (timeout < k_MaxTimeout){
		uint32_t newTimeout = osKernelGetTickFreq() * (timeout / 1000);
		return osSemaphoreAcquire(event, newTimeout);
	} else
		return osSemaphoreAcquire(event, timeout);
}

inline osStatus_t Signal(osSemaphoreId_t event){
	return osSemaphoreRelease(event);
}

void Init();

}
}

#endif /* INC_EVENTS_EVENTS_HPP_ */
