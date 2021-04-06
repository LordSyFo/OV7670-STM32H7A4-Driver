/*
 * IProcess.h
 *
 *  Created on: Sep 18, 2020
 *      Author: SYFO
 */

#ifndef INC_UTIL_APROCESS_H_
#define INC_UTIL_APROCESS_H_

namespace Util {

class AProcess {
public:
	AProcess(){}

	virtual void OnEnter(){};
	virtual void Run(){};
	virtual void OnExit(){};

	virtual ~AProcess(){}
};

} /* namespace Util */

#endif /* INC_UTIL_APROCESS_H_ */
