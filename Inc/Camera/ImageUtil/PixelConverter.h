/*
 * PixelConverter.h
 *
 *  Created on: 7 Oct 2020
 *      Author: SYFO
 */

#ifndef INC_CAMERA_IMAGEUTIL_PIXELCONVERTER_H_
#define INC_CAMERA_IMAGEUTIL_PIXELCONVERTER_H_

#include <Camera/ImageUtil/IPixelConverter.h>
#include <cstring>

namespace ImageUtil {

class PixelConverter : public IPixelConverter {
public:
	PixelConverter(){}

	template<typename T>
	inline uint8_t clamp(T val, T min, T max){
		return val > max ? max : val < min ? min : val;
	}

	/*
	 *
	 * @param	srcCount	Number of bytes to be converted
	 * */
	int ConvertYUVtoRGB(uint8_t* src, int srcCount, uint8_t* dest)
	{

		 /* Atm it is not supported to convert pixels to RGB and store them in the same destination as
		 * the source.*/
		if (src == dest) throw NotSupported();
		if (src == nullptr || dest == nullptr) throw InvalidParameter();
		//TODO: Throw if the srcCount is bigger than the maximum ram allocation allowed

		uint8_t rgb[6];
		int arrSize = sizeof(rgb);
		int copyCount = 0;

		// Loop through each pixel
		for (int i = 0; i < srcCount; i+=4){
			float u = src[i];
			float y0 = src[i+1];
			float v = src[i+2];
			float y1 = src[i+3];

			// Convert to RGB (credit: https://thinksmallthings.wordpress.com/2012/11/03/ov7670-yuv-demystified/comment-page-1/)
			rgb[0] = clamp(y0 + 1.4075 * (v-128.0), 0.0, 255.0);
			rgb[1] = clamp(y0 - 0.3455 * (u-128.0) - (0.581*(v-128)),0.0,255.0);
			rgb[2] = clamp(y0 + 1.7790 * (u-128.0), 0.0,255.0);

			rgb[3] = clamp(y1 + 1.4075 * (v-128.0), 0.0,255.0);
			rgb[4] = clamp(y1 - 0.3455 * (u-128.0) - (0.581*(v-128.0)), 0.0,255.0);
			rgb[5] = clamp(y1 + 1.7790 * (u-128.0) ,0.0,255.0);

			// Copy to destination
			memcpy(dest + copyCount, rgb, arrSize);
			copyCount += arrSize;

		}

		return copyCount;

	}

	virtual ~PixelConverter(){}
};

} /* namespace ImageUtil */

#endif /* INC_CAMERA_IMAGEUTIL_PIXELCONVERTER_H_ */
