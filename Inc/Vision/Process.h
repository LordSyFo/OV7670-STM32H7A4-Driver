/*
 * Process.h
 *
 *  Created on: Nov 9, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_VISION_PROCESS_H_
#define INC_VISION_PROCESS_H_

#include <Compression/ICompressor.h>
#include <Video/IController.h>

#include <Camera/OV7670.h>
#include <Util/AProcess.h>
#include <cmsis_os2.h>

#include <algorithm>
#include <cstring>

extern Storage::SD g_SDCard;

namespace Vision {

class Process: public Util::AProcess {
public:
	Process(Camera::OV7670& camera, Video::IVideoController& videoCtrl ) : camera_(camera), videoCtrl_(videoCtrl) {}

	void OnEnter()
	{
		camera_.Initialize();	// Must be done after low-level hardware initializations
		videoCtrl_.Initialize();
	}

	void Run()
	{

		uint32_t count = 1;

		while(1){
			// Capture an image
			bool status = camera_.CaptureImageAsync();	// Async in a way such that it lets other threads roam while waiting for signals

			if (status){

				videoCtrl_.Handle(camera_.GetImageData8());

			}
		}
	}

	void OnExit(){}

	virtual ~Process(){}

private:
	Camera::OV7670& camera_;

	Video::IVideoController& videoCtrl_;
};

} /* namespace Vision */

#endif /* INC_VISION_PROCESS_H_ */
