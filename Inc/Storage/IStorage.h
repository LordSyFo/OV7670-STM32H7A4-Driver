/*
 * IStorage.h
 *
 *  Created on: 3 Nov 2020
 *      Author: SYFO
 */

#ifndef INC_STORAGE_ISTORAGE_H_
#define INC_STORAGE_ISTORAGE_H_

#include <stdint.h>

namespace Storage {

class IStorage {
public:
	IStorage(){}

	virtual unsigned int WriteToFile(const char* fileName, uint8_t* buffer, uint32_t bufferLen) = 0;

	virtual void AppendToFile(const char* fileName, uint8_t* buffer, uint32_t bufferLen) = 0;

	virtual unsigned int ReadFromFile(const char* fileName, uint8_t* buffer, uint32_t maxReadLen) = 0;
	virtual bool ReadLine(const char* fileName, uint8_t* buffer, uint32_t maxReadLen) = 0;

	virtual void ResetRead() = 0;

	virtual unsigned int GetNumberOfFilesInDir(const char* directory) = 0;

	virtual void Initialize() = 0;

	virtual ~IStorage(){}
};

} /* namespace Storage */

#endif /* INC_STORAGE_ISTORAGE_H_ */
