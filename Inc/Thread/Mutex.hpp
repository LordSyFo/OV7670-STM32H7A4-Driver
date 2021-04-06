/*
 * Mutex.hpp
 *
 *  Created on: Nov 5, 2020
 *      Author: SYFO
 */

#ifndef INC_THREAD_MUTEX_HPP_
#define INC_THREAD_MUTEX_HPP_

#include <cmsis_os2.h>

namespace Thread {
namespace Mutex {

template<osMutexId_t& mutex>
class scoped_lock{
	scoped_lock(){
		osMutexAcquire(mutex, osWaitForever);
	}

	~scoped_lock(){
		osMutexRelease(mutex);
	}
};

/* Mutex list */
template<osMutexId_t&... Mutexes>
struct MutexList {
	static constexpr int size = sizeof...(Mutexes);
	osMutexId_t array[sizeof...(Mutexes)] = {Mutexes...};
};

extern osMutexId_t k_SettingsManagerMutex;		// Used to lock settingsmanager access

extern MutexList<k_SettingsManagerMutex> k_MutexList;

/* Methods */
inline void InitializeMutex(osMutexId_t& mutex){
	const osMutexAttr_t Thread_Mutex_attr = {
	  "",                          				// human readable mutex name
	  osMutexRecursive | osMutexPrioInherit,    // attr_bits
	  NULL,                                     // memory for control block
	  0U                                        // size for control block
	};

	mutex = osMutexNew(&Thread_Mutex_attr);
}

inline void Init(){
	for (int i = 0; i < k_MutexList.size; i++)
		InitializeMutex(k_MutexList.array[i]);
}


}
}
#endif /* INC_THREAD_MUTEX_HPP_ */
