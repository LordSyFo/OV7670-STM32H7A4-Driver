/*
 * CameraExceptions.h
 *
 *  Created on: 6 Oct 2020
 *      Author: SYFO
 */

#ifndef INC_CAMERA_CAMERAEXCEPTIONS_H_
#define INC_CAMERA_CAMERAEXCEPTIONS_H_

#include <Util/BaseException.h>

class CameraException : public BaseException {};

class HeaderFormatError : public CameraException {};



#endif /* INC_CAMERA_CAMERAEXCEPTIONS_H_ */
