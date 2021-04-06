/*
 * PixelConverterExceptions.h
 *
 *  Created on: 7 Oct 2020
 *      Author: SYFO
 */

#ifndef INC_CAMERA_IMAGEUTIL_PIXELCONVERTEREXCEPTIONS_H_
#define INC_CAMERA_IMAGEUTIL_PIXELCONVERTEREXCEPTIONS_H_

#include <Util/BaseException.h>

class PixelConverterException : public BaseException {};

class NotSupported : public PixelConverterException {};
class InvalidParameter : public PixelConverterException {};

#endif /* INC_CAMERA_IMAGEUTIL_PIXELCONVERTEREXCEPTIONS_H_ */
