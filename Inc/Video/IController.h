/*
 * IController.h
 *
 *  Created on: 12 Nov 2020
 *      Author: SYFO
 */

#ifndef INC_VIDEO_ICONTROLLER_H_
#define INC_VIDEO_ICONTROLLER_H_

namespace Video {

class IController {
public:
	IController(){}

	virtual void Handle(uint8_t* src) = 0;
	virtual void Initialize() = 0;

	virtual ~IController(){}
};

} /* namespace Video */

#endif /* INC_VIDEO_ICONTROLLER_H_ */
