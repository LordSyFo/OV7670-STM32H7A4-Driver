/*
 * OV7670.h
 *
 *  Created on: Sep 15, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_CAMERA_OV7670_H_
#define INC_CAMERA_OV7670_H_

#include "stdint.h"
#include <Serial/I2C.h>
#include <Util/Interruptable.h>
#include <Camera/ImageUtil/Image.h>
#include <Serial/ISerial.h>
#include <Camera/OV7670Settings.h>

#include <Camera/CameraExceptions.h>
#include <Camera/ImageUtil/IPixelConverter.h>

namespace Camera {

#define DEVICE_ADDRESS 0x42	// write and 43 for read

/* Setting structures */

// We only use images in YUV but we can transform them to RGB
enum class ColorMode{
	kYUV = 2,		// 2 Bytes per pixel
};

enum class TransmissionMode {
	kGrayscale = 0,
	kRGBFullscale = 1,
	kYUVFullscale = 2
};

typedef struct Resolution{
	unsigned int width;
	unsigned int height;
} Resolution;

class OV7670 : public Util::Interruptable {

public:
	using YUVImageType = Image<174,144,2>;	// Max image size

public:
	OV7670(Serial::I2C& i2c,DCMI_HandleTypeDef& dcmi,
			DMA_HandleTypeDef& dma,
			TIM_HandleTypeDef& timeout_timer,
			ImageUtil::IPixelConverter& pixelConverter);

	void WriteToRegister(const uint8_t reg, const uint8_t* data, const uint16_t count);
	void ReadFromRegister(const uint8_t reg, uint8_t* data, const uint16_t count);

	/* Initializers */
	void Initialize();

	/* Camera setting methods */
	void ApplySettings(const Setting* settings, uint16_t size);
	void ResetCamera();

	/* Inherited from Interruptable */
	void OnInterrupt(uint16_t sig);

	/* Image acquisition methods */
	bool CaptureImage();										// Capture with in-class image buffer
	bool CaptureImage(uint32_t frameBuffer,unsigned int size);	// Capture with external image buffer
	bool CaptureImageAsync(uint32_t frameBuffer,unsigned int size);	// Capture with thread waits
	bool CaptureImageAsync();

	inline uint16_t* GetImageData16(){return reinterpret_cast<uint16_t*>(YUVImage_.GetDataPointer());}	// Return data-pointer to image
	inline uint8_t* GetImageData8(){return YUVImage_.GetDataPointer();}		// Return data-pointer to image

	uint8_t* GetRGBImage(int& count);

	/* Image transfer methods */
	void TransferImage(Serial::ISerial* serial,TransmissionMode mode);

	/* Color transformation methods */
	inline uint8_t RGBToGrayscale(uint8_t r, uint8_t g, uint8_t b) {return 0.3*r + 0.59*g + 0.11*b;}

	virtual ~OV7670();
private:

	/* Image transfer methods */
	void TransferGrayscale(Serial::ISerial* serial, int nPixels);
	void TransferFullscaleRGB(Serial::ISerial* serial, int nPixels);
	void TransferFullscaleYUV(Serial::ISerial* serial, int nPixels);

	Serial::I2C& i2c_;

	YUVImageType YUVImage_;
	//RGBImageType RGBImage_;

	ImageUtil::IPixelConverter& pixelConverter_;

	DCMI_HandleTypeDef& dcmi_;
	DMA_HandleTypeDef& dcmiDma_;

	volatile bool captured_;
	volatile bool error_;

	TIM_HandleTypeDef& timeoutTimer_;

	// Camera settings
	ColorMode mode_;
	Resolution resolution_;

	const Setting* resSettings_;
	uint16_t resSettingsSize_;

};

} /* namespace Camera */

#endif /* INC_CAMERA_OV7670_H_ */
