/*
 * ICompressor.h
 *
 *  Created on: 6 Nov 2020
 *      Author: SYFO
 */

#ifndef INC_COMPRESSION_ICOMPRESSOR_H_
#define INC_COMPRESSION_ICOMPRESSOR_H_

#include <stdint.h>

namespace Compression {

class ICompressor {
public:
	ICompressor(){};

	/* Returns new size! */
	virtual uint8_t* Compress(uint8_t* src) = 0;

	virtual uint8_t* GetCompressedFile() = 0;

	virtual uint32_t GetFileSize() = 0;

	virtual ~ICompressor(){};
};

} /* namespace Compression */

#endif /* INC_COMPRESSION_ICOMPRESSOR_H_ */
