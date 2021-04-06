/*
 * Accessor.h
 *
 *  Created on: Nov 5, 2020
 *      Author: SYFO
 */

#ifndef INC_THREAD_ACCESSOR_H_
#define INC_THREAD_ACCESSOR_H_

#include "cmsis_os.h"

namespace Thread{

// https://members.accu.org/index.php/articles/1967

// https://www.boost.org/doc/libs/1_41_0/boost/noncopyable.hpp
class noncopyable
{
protected:
  noncopyable() {}
  ~noncopyable() {}
private:  // emphasize the following members are private
  noncopyable( const noncopyable& );
  const noncopyable& operator=( const noncopyable& );
};

template <typename T>
class UniqueAccessGuard : public noncopyable{

public:
	UniqueAccessGuard() : value_() {}
	UniqueAccessGuard(T& value) : value_(value) {}

	void PostInit(){

		const osMutexAttr_t Thread_Mutex_attr = {
		  "myThreadMutex",                          // human readable mutex name
		  osMutexRecursive | osMutexPrioInherit,    // attr_bits
		  NULL,                                     // memory for control block
		  0U                                        // size for control block
		};

		mutex_ = osMutexNew(&Thread_Mutex_attr);
		if (mutex_id != NULL)  {
		    assert(false);
		}
	}

private:
	T value_;
	osMutexId_t mutex_;
};




}

#endif /* INC_THREAD_ACCESSOR_H_ */
