/*
 * BaseImage.h
 *
 *  Created on: Oct 1, 2020
 *      Author: SYFO
 */

#ifndef INC_CAMERA_BASEIMAGE_H_
#define INC_CAMERA_BASEIMAGE_H_

namespace Camera {

typedef unsigned int uint;

class BaseImage {
public:
	BaseImage(){}

	virtual uint GetWidth() const = 0;
	virtual uint GetHeight() const = 0;

	virtual uint8_t* GetDataPointer() = 0;

	virtual ~BaseImage(){}
};

} /* namespace Camera */

#endif /* INC_CAMERA_BASEIMAGE_H_ */
