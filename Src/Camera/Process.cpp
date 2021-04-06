/*
 * Process.cpp
 *
 *  Created on: 27 Oct 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#include <Camera/Process.h>
#include <Serial/ISerial.h>
#include <Camera/ImageUtil/Image.h>
#include <Compression/JPEG.h>
#include "cmsis_os.h"

namespace Camera {

Process::Process(OV7670& camera, Serial::ISerial& serial) : camera_(camera), serial_(serial) {
	// TODO Auto-generated constructor stub
}

void Process::Run(){
	while(1){
		// Acquire image (Camera testing code)
		bool status = camera_.CaptureImageAsync();

		if (status)
			try{
				camera_.TransferImage(&serial_,Camera::TransmissionMode::kRGBFullscale);
			} catch (...){}
	}
}

Process::~Process() {
	// TODO Auto-generated destructor stub
}

} /* namespace Camera */
