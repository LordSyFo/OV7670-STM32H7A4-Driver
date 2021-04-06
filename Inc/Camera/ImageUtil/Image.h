/*
 * Image.h
 *
 *  Created on: Sep 24, 2020
 *      Author: SYFO
 */

#ifndef INC_CAMERA_IMAGE_H_
#define INC_CAMERA_IMAGE_H_

#include <Camera/ImageUtil/BaseImage.h>

namespace Camera {

typedef unsigned int uint;

template<uint Width, uint Height, uint BytesPrPixel>
class Image : BaseImage {
public:
	Image(){}

	uint GetWidth() const { return Width; }
	uint GetHeight()const { return Height; }

	uint8_t* GetDataPointer(){return pixel_data;}

	virtual ~Image(){}
private:
	uint8_t pixel_data[Width * Height * BytesPrPixel] = {0};

};

} /* namespace Camera */

#endif /* INC_CAMERA_IMAGE_H_ */
