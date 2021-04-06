/*
 * IPixelConverter.h
 *
 *  Created on: 7 Oct 2020
 *      Author: SYFO
 */

#ifndef INC_CAMERA_IMAGEUTIL_IPIXELCONVERTER_H_
#define INC_CAMERA_IMAGEUTIL_IPIXELCONVERTER_H_

#include <stdint.h>
#include <Camera/ImageUtil/PixelConverterExceptions.h>

namespace ImageUtil {

class IPixelConverter {
public:
	IPixelConverter(){}

	virtual int ConvertYUVtoRGB(uint8_t* src, int pixelCount, uint8_t* dest) = 0;

	virtual ~IPixelConverter(){}
};

} /* namespace ImageUtil */

#endif /* INC_CAMERA_IMAGEUTIL_IPIXELCONVERTER_H_ */
