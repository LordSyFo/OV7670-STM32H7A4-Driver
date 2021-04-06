/*
 * Process.h
 *
 *  Created on: 27 Oct 2020
 *      Author: SYFO
 */

#ifndef INC_CAMERA_PROCESS_H_
#define INC_CAMERA_PROCESS_H_

#include <Util/AProcess.h>
#include <Camera/OV7670.h>

namespace Camera {

class Process : Util::AProcess {
public:
	Process(OV7670& camera, Serial::ISerial& serial);

	void Run();

	virtual ~Process();
private:
	OV7670& camera_;
	Serial::ISerial& serial_;
};

} /* namespace Camera */

#endif /* INC_CAMERA_PROCESS_H_ */
