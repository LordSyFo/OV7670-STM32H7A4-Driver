/*
 * OV7670.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: SYFO
 */

#include <Camera/OV7670.h>
#include <string.h>
#include "stm32h7xx_hal.h"
#include <cassert>
#include <stdio.h>
#include <Thread/Events/Events.hpp>

namespace Camera {

#define FRAME_INTERRUPT 0
#define DCMI_ERROR 0xFF
#define DCMI_TIMEOUT 0xF0

//TODO: Make these inline instead because we are c++ cool
#define APPLY_STATIC_SETTING(setting) 	(ApplySettings(setting,sizeof(setting)/sizeof(Setting)))
#define CAST_INT(enumval)				(static_cast<int>(enumval))

/***** Class methods ******/
OV7670::OV7670(Serial::I2C& i2c,DCMI_HandleTypeDef& dcmi,DMA_HandleTypeDef& dma,
		TIM_HandleTypeDef& timeout_timer,ImageUtil::IPixelConverter& pixelConverter) :
		i2c_(i2c),
		dcmi_(dcmi),
		dcmiDma_(dma),
		timeoutTimer_(timeout_timer),
		pixelConverter_(pixelConverter)
{
}

/*
 * Initialize the OV7670 Camera module.
 *
 * This method initializes the OV7670 Camera module with predetermined optimal settings.
 *
 * */
void OV7670::Initialize()
{

	// Save color mode and resolution based on defines
#ifdef USE_YUV_QCIF
	mode_ = ColorMode::kYUV;
	resolution_.height = 144;
	resolution_.width = 174;	// Very odd but OV7670 uses 174 instead of 176 for some unknown reason?
	resSettings_ = kQCIF_YUV_Settings;
	resSettingsSize_ = sizeof(kQCIF_YUV_Settings) / sizeof(Setting);
#endif

	// Apply settings
	try {
		// Reset camera settings
		ResetCamera();
		APPLY_STATIC_SETTING(kExternSettings);			// Upload settings from interwebz
		ApplySettings(resSettings_, resSettingsSize_);	// Upload resolution settings

	} catch (const I2CException& e){
		// OOPS Settings did not get uploaded without errors
		assert(false);
	}

	HAL_Delay(1000);	// Wait a second after applying settings
}


/*
 * Write to an OV7670 register.
 *
 * Use this method to write data to a specific register on the OV7670-module.
 *
 * @param ´reg´ 	OV7670 Register. (registers can be found in the datasheet)
 * @param ´data´ 	Data to be transmitted.
 * @param ´count´	The number of bytes to transmit.
 * */
void OV7670::WriteToRegister(const uint8_t reg, const uint8_t* data, const uint16_t count)
{
	// Setup error handling variables
	uint8_t retries = 0;
	uint8_t max_retries = 10;

	while(retries<max_retries){
		try {
			// Write address, register and desired data.
			i2c_.WriteToReg(DEVICE_ADDRESS, reg, data, count);
			break;
		} catch (const I2CException& e) {
			//TODO: Maybe react different depending on the type of error (timeout, busy or unspecified?)
			if (retries++>=max_retries) throw;	// rethrow incase we exceed max retries
		}
	}
}

/*
 * Read from an OV7670 register.
 *
 * Use this method to read from a specific register on the OV7670-module.
 *
 * @param ´reg´ 	OV7670 Register. (registers can be found in the datasheet)
 * @param ´data´ 	Data container for the read data.
 * @param ´count´	The maximum number of bytes to read.
 * */
void OV7670::ReadFromRegister(uint8_t reg, uint8_t* data, uint16_t count)
{
	// Setup error handling variables
	uint8_t retries = 0;
	uint8_t max_retries = 10;

	while(retries<max_retries){
		try {

			// Write address and register in write-mode
			i2c_.Write(DEVICE_ADDRESS, &reg, 1);

			// Write address and read
			i2c_.ReadFromReg(DEVICE_ADDRESS, reg, data, count);

			break;
		} catch (const I2CException& e) {
			//TODO: Maybe react different depending on the type of error (timeout, busy or unspecified?)
			if (retries++>=max_retries) throw;	// rethrow incase we exceed max retries
		}
	}

}

void OV7670::OnInterrupt(uint16_t sig)
{
	if (sig == FRAME_INTERRUPT){
		captured_ = true;
		error_ = false;
	} else if(sig == DCMI_ERROR){
		captured_ = true;	// Set true so we leave the while
		error_ = true;
	} else if(sig == DCMI_TIMEOUT){
		// Timer is automatically disabled after interrupt
		captured_ = true;	// Set true so we leave the while
		error_ = true;
	}

}

/*
 * Capture an image with the internal image buffer.
 *
 * Use this method to capture an image using the internal pixel buffer.
 *
 * @return True if capture was successful, false otherwise.
 * */
bool OV7670::CaptureImage(){
	// Behold the ugliest function call ever
	return CaptureImage((uint32_t)YUVImage_.GetDataPointer(),
			(resolution_.width * resolution_.height * CAST_INT(mode_)) / 4);
}

/*
 * Capture an image with a user-specified data buffer.
 *
 * Use this method to capture an image using an external buffer for storing the pixels.
 *
 * @param ´frameBuffer´ Data pointer casted to a uint32_t
 * @param ´size´ 		Size of the image in bytes
 * @return True if capture was successful, false otherwise.
 * */
bool OV7670::CaptureImage(uint32_t frameBuffer,unsigned int size)
{
	if (size <= 0)
		return false;

	captured_ = false;
	error_ = true;

	uint8_t retries = 0;
	uint8_t max_retries = 10;

	while(error_ && retries!=max_retries){

		// Stop the current transfer if any
		HAL_DCMI_Stop(&dcmi_);

		//__HAL_DCMI_RESET_HANDLE_STATE() TODO: These macros can very well come in handy!

		HAL_StatusTypeDef status = HAL_DCMI_Start_DMA(&dcmi_, DCMI_MODE_SNAPSHOT, (uint32_t)frameBuffer, size);

		if (status != HAL_OK)
			return false;

		// Start timer to generate timeout in case of deadlock errors (2s TODO: Make this timeout way earlier like 500sms)
		HAL_TIM_Base_Start_IT(&timeoutTimer_);

		while(!captured_);	// Wait for frame interrupt

		retries++;

		HAL_TIM_Base_Stop_IT(&timeoutTimer_);	// Disable the timer

	}

	return !error_;

}

/*
 * Capture an image with the internal image buffer using thread efficient techniques.
 *
 * Use this method to capture an image using the internal pixel buffer, optimized for a threaded environment.
 *
 * @return True if capture was successful, false otherwise.
 * */
bool OV7670::CaptureImageAsync()
{
	// Behold the ugliest function call ever
	return CaptureImageAsync((uint32_t)YUVImage_.GetDataPointer(),
			(resolution_.width * resolution_.height * CAST_INT(mode_)) / 4);
}

/*
 * Capture an image with an external image buffer using thread efficient techniques.
 *
 * Use this method to capture an image using an external pixel buffer, optimized for a threaded environment.
 *
 * @param ´frameBuffer´ Data pointer casted to a uint32_t
 * @param ´size´ 		Size of the image in bytes
 * @return True if capture was successful, false otherwise.
 * */
bool OV7670::CaptureImageAsync(uint32_t frameBuffer,unsigned int size)
{
	if (size <= 0)
		return false;

	uint8_t retries = 0;
	uint8_t max_retries = 10;

	while(retries!=max_retries){

		// Stop the current transfer if any
		HAL_DCMI_Stop(&dcmi_);
		HAL_StatusTypeDef status = HAL_DCMI_Start_DMA(&dcmi_, DCMI_MODE_SNAPSHOT, (uint32_t)frameBuffer, size);

		if (status != HAL_OK)
			return false;

		osStatus_t eventStatus = Thread::Events::Wait(Thread::Events::DCMIFrameCaptureEvent, 1000);

		// If transmission was succesful
		if (eventStatus != osErrorTimeout)
			break;

		retries++;

	}

	return ! (retries==max_retries);
}

/*
 * Transfer a captured image using an arbitrary ISerial-instance.
 *
 * Use this method to transfer a captured image using an arbitrary ISerial-instance.
 *
 * @param ´serial´	Instance of a Serial class used for transmission
 * @param ´mode´	Mode of transmission (color-format)
 * */
void OV7670::TransferImage(Serial::ISerial* serial,TransmissionMode mode = TransmissionMode::kRGBFullscale)
{
	// Check if there is an image in the buffer
	if (*(YUVImage_.GetDataPointer())!=0){

		// Convert image size to string
		char imgHeader[20];
		int nPixels = resolution_.width * resolution_.height;

		/*
		 * Image header contains
		 * 	- Image width
		 * 	- Image height
		 * 	- Bytes per pixel
		 * 	- Transmission mode
		 * */
		/*int n = sprintf(imgHeader,"\n%d%d%d\n",
				resolution_.width,
				resolution_.height,
				static_cast<int>(mode));*/

		// Create binary header
		imgHeader[0] = '\n';
		memcpy(imgHeader+1, &resolution_.width, sizeof(resolution_.width));
		memcpy(imgHeader+1+sizeof(resolution_.width), &resolution_.height, sizeof(resolution_.height));
		memcpy(imgHeader+1+sizeof(resolution_.width)+sizeof(resolution_.height), &mode, sizeof(int));
		int n = 1+sizeof(resolution_.width)+sizeof(resolution_.height)+sizeof(int);

		if (n<0)
			throw HeaderFormatError();	// If there was an error formatting the image-header

		// Transmit header
		serial->Write(0, (uint8_t*)imgHeader, n);

		HAL_Delay(1000);	// Wait a second for the PC-software to get ready

		// Switch on the transmission mode
		switch(mode){
			case TransmissionMode::kGrayscale:
				TransferGrayscale(serial,nPixels);
				break;
			case TransmissionMode::kYUVFullscale:
				TransferFullscaleYUV(serial,nPixels);
				break;
			case TransmissionMode::kRGBFullscale:
				TransferFullscaleRGB(serial,nPixels);
				break;
		}
	}
}

void OV7670::TransferFullscaleYUV(Serial::ISerial* serial, int nPixels)
{
	// 2 Bytes per pixel
	uint8_t* imgBuffer = GetImageData8();	// Save a local pointer to the image buffer
	for (int i = 0; i < nPixels*2; i++){
		serial->Write(0, imgBuffer+i, 1);
	}
}

uint8_t* OV7670::GetRGBImage(int& count)
{
	// Check if there is an image in the buffer
	/*if (*(YUVImage_.GetDataPointer())!=0)
	{
		int nPixels = resolution_.width * resolution_.height;

		// Get datapointer
		uint8_t* YUVBuffer = GetImageData8();
		int YUVDataSize = nPixels*2;
		uint8_t* RGBBuffer = (uint8_t*)RGBImage_.GetDataPointer();

		// Convert YUV to RGB
		try {
			count = pixelConverter_.ConvertYUVtoRGB(YUVBuffer, YUVDataSize, RGBBuffer);
		} catch (...){
			count = -1;
			throw;	// rethrow
		}

		return RGBBuffer;
	}*/

	return nullptr;	// Not implemented
}

void OV7670::TransferFullscaleRGB(Serial::ISerial* serial, int nPixels)
{
	/*
	try {
			int count = -1;
			uint8_t* RGBBuffer = GetRGBImage(count);

			// Transmit RGB pixels if the conversion was completed
			if (count != -1)
				for (int i = 0; i < count; i++)
					serial->Write(0, RGBBuffer+i, 1);

	} catch (...){
		return;
	}*/
	return; 	// Not implemented
}

void OV7670::TransferGrayscale(Serial::ISerial* serial, int nPixels){

	uint16_t* imgBuffer = GetImageData16();	// Save a local pointer to the image buffer

	for (int i = 0; i < nPixels; i++){
		// Send every other pixel resulting in a gray-scale image
		serial->Write(0, ((uint8_t*)imgBuffer)+i+i+1, 1);	// TODO: Add exception safety to all ISerial classes
	}

}

/*
 * Reset camera
 *
 * Perform a software reset on the camera.
 *
 * */
void OV7670::ResetCamera()
{
	// Setup error handling variables
	uint8_t retries = 0;
	uint8_t max_retries = 10;
	uint8_t reset = 0b10000000;

	while(retries<max_retries){
		try {
			WriteToRegister(0x12, &reset, 1);
			break;
		} catch (const I2CException& e) {
			//TODO: Maybe react different depending on the type of error (timeout, busy or unspecified?)
			if (retries++>=max_retries) throw;	// rethrow incase we exceed max retries
		}
	}

	HAL_Delay(200);	// Wait after resetting!

}

/*
 * Apply settings to the camera
 *
 * Apply specified settings to the camera.
 *
 * @param ´settings´	Pointer to settings-array containing reg/value pairs.
 * @param ´size´		Number of settings in array
 * */
void OV7670::ApplySettings(const Setting* settings, uint16_t size)
{
	if (settings == nullptr || size == 0) return;

	// Loop through settings and upload to Camera
	for (uint16_t i = 0; i < size; i++)
		WriteToRegister(settings[i].reg, &settings[i].value, 1);
}

OV7670::~OV7670() {
	// TODO Auto-generated destructor stub
}

} /* namespace Camera */
