/*
 * JPEGCompressor.h
 *
 *  Created on: 6 Nov 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_COMPRESSION_JPEG_H_
#define INC_COMPRESSION_JPEG_H_

#include <cassert>

#include <Compression/ICompressor.h>
#include "stm32h7xx_hal.h"

namespace Compression {

namespace Symbol{
	constexpr uint8_t k_JPEGTrailer[] = {0xff, 0xd9};
}

template<uint32_t Width, uint32_t Height, uint32_t HBlockSize = 8, uint32_t VBlockSize = 8>
class JPEGCompressor : public ICompressor {
public:
	JPEGCompressor(JPEG_HandleTypeDef& handle) : handle_(handle) {}

	void ConvertYUV422ToMCUBlocks(uint8_t* src){

		uint32_t YOffset = 0;
		uint32_t CbOffset = 64;
		uint32_t CrOffset = 128;

		uint32_t total_count = 0;
		uint8_t stepSize = 4;

		/* Loop through each VBlock */
		for (int vblock = 0; vblock < nVBlocks; vblock++) {
			/* Loop through each HBlock */
			for (int hblock = 0; hblock < nHBlocks; hblock++) {
				uint32_t nBlocksDone = hblock + vblock * nHBlocks;
				total_count = nBlocksDone * BlockSize * 3;

				/* Loop through block height by width */
				for (int y = 0; y < VBlockSize; y++) {
					for (int x = 0; x < HBlockSize; x+=2) {

						// This should store both the Y, Cb and Cr with fitting offsets!
						uint32_t xOffset = hblock * HBlockSize * 2;
						uint32_t yOffset = vblock * VBlockSize;

						uint32_t xStep = x / 2 * stepSize + xOffset;
						uint32_t yStep = (y+yOffset) * ImageWidth * 2;

						uint32_t pixelIdx = xStep + yStep;


						/* In case we havent got enough pixels */
						if (pixelIdx >= Height * Width * 2) {
							return;	// Just ignore the rest of the spots
						}

						// Store Y-values
						MCUBuffer[total_count + YOffset] 		= src[pixelIdx + 1];
						MCUBuffer[total_count + YOffset + 1] 	= src[pixelIdx + 3];

						// Store Cb values
						MCUBuffer[total_count + CbOffset] 		= src[pixelIdx];
						MCUBuffer[total_count + CbOffset + 1] 	= src[pixelIdx];

						// Store Cr values
						MCUBuffer[total_count + CrOffset] 		= src[pixelIdx + 2];
						MCUBuffer[total_count + CrOffset + 1] 	= src[pixelIdx + 2];

						total_count += 2;	// Might be more suitable instead of [x+y*Blocksize]
					}
				}
			}
		}

	}

	uint8_t* Compress(uint8_t* src)
	{

		HAL_StatusTypeDef status;

		/* Config encoding */
		JPEG_ConfTypeDef config = {
				JPEG_YCBCR_COLORSPACE,	// Colorspace
				JPEG_444_SUBSAMPLING,	// Chroma Subsampling
				Height,					// Image Height
				Width,					// Image Width
				80,						// Image quality (1-100)
		};

		status = HAL_JPEG_ConfigEncoding(&handle_, &config);

		ConvertYUV422ToMCUBlocks(src);

		if (status == HAL_OK)
			status = HAL_JPEG_Encode(&handle_, MCUBuffer, MCUBufferSize, jpegBuffer,k_maxSize, 10000);

		return status == HAL_OK ? GetCompressedFile() : nullptr;
	}

	uint8_t* GetCompressedFile()
	{
		return jpegBuffer;
	}

	uint32_t GetFileSize()
	{
		// Find trailer signature
		uint32_t i = 0;
		while(i<k_maxSize-1){
			if (jpegBuffer[i]==Symbol::k_JPEGTrailer[0] && jpegBuffer[i+1]==Symbol::k_JPEGTrailer[1])
				return i+2;
			i++;
		}

		return 0;
	}

	virtual ~JPEGCompressor(){}

private:
	JPEG_HandleTypeDef& handle_;
	static const uint32_t k_maxSize = Width*Height;

public:
	uint8_t jpegBuffer[k_maxSize];		// For quality=100 max bits pr pixel is about 8.25

	/* Variables for MCU subsampling */
	static constexpr uint32_t nHBlocks = static_cast<int>(((float)Width / HBlockSize) + 0.95);
	static constexpr uint32_t nVBlocks = static_cast<int>(((float)Height / VBlockSize) + 0.95);
	static constexpr uint32_t BlockSize = HBlockSize * VBlockSize;

	static constexpr uint32_t MCUBufferSize = nHBlocks * nVBlocks * BlockSize * 3;	// One block per channel (Y Cb Cr)

	uint8_t MCUBuffer[MCUBufferSize];	// Buffer for all blocks (3 because we must save Y, Cb and Cr)

	static constexpr uint32_t ImageSize		= Height * Width;
	static constexpr uint32_t ImageWidth	= Width;
	static constexpr uint32_t ImageHeight	= Height;
};

} /* namespace Compression */

#endif /* INC_COMPRESSION_JPEG_H_ */
