/*
 * IVideoController.h
 *
 *  Created on: 13 Nov 2020
 *      Author: SYFO
 */

#ifndef INC_VIDEO_IVIDEOCONTROLLER_H_
#define INC_VIDEO_IVIDEOCONTROLLER_H_

#include <Video/IController.h>
#include <Video/Types.h>

namespace Video {

class IVideoController : public IController {
public:
	IVideoController(){}

	virtual void Handle(uint8_t* src) = 0;
	virtual void Initialize() = 0;

	virtual void Save() = 0;
	virtual uint32_t GetVideoSize(uint32_t vidIdx) = 0;

	virtual uint8_t GetVideoAmount() = 0;
	virtual uint32_t GetImagesAmount(uint32_t vidIdx) = 0;

	virtual VideoInfoFile GetVideoInformation(uint32_t videoIdx) = 0;

	virtual uint32_t GetStoredImage(uint32_t videoNumber, uint32_t imageNumber, uint8_t* buffer, uint32_t bufSize) = 0;

	virtual ~IVideoController(){}
};

} /* namespace Video */

#endif /* INC_VIDEO_IVIDEOCONTROLLER_H_ */
