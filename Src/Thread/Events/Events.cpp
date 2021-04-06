/*
 * Events.cpp
 *
 *  Created on: Oct 25, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */
#include <Thread/Events/Events.hpp>

namespace Thread{
namespace Events{

osSemaphoreId_t SPISelectEvent;
osSemaphoreId_t DCMIFrameCaptureEvent;

osSemaphoreId_t* g_Semaphores[] = {
		&SPISelectEvent,
		&DCMIFrameCaptureEvent
};

constexpr int nSemaphores = sizeof(g_Semaphores) / sizeof(g_Semaphores[0]);

void Init(){
	for (int i = 0; i < nSemaphores; i++)
		*g_Semaphores[i] = osSemaphoreNew(1, 0, NULL);
}

}
}
