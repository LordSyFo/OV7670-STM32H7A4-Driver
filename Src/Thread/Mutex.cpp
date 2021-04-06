/*
 * Mutex.cpp
 *
 *  Created on: Nov 5, 2020
 *      Author: SYFO
 */

#include <cmsis_os2.h>
#include <Thread/Mutex.hpp>

namespace Thread{
namespace Mutex{

// Create list of used mutexes
osMutexId_t k_SettingsManagerMutex;		// Used to lock settingsmanager access

MutexList<k_SettingsManagerMutex> k_MutexList;


}
}
