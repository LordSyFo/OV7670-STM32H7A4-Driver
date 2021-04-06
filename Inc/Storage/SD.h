/*
 * SD.h
 *
 *  Created on: 3 Nov 2020
 *      Author: SYFO
 */

#ifndef INC_STORAGE_SD_H_
#define INC_STORAGE_SD_H_

#include <Storage/IStorage.h>
#include "fatfs.h"

namespace Storage {

class SDIterator {
public:

	SDIterator(FILINFO* intial, DIR* directory) : currentEntry_(intial), currentDirectory_(directory) {}

	FILINFO& operator*(){ return *currentEntry_; }
	FILINFO* operator->() {return currentEntry_; }

	// Pre
	SDIterator operator++(){
		FRESULT fres;
		fres = f_readdir(currentDirectory_, currentEntry_);

		if (fres != FR_OK || currentEntry_->fname[0] == 0){
			currentEntry_ = nullptr;	// end of list

			// Close directory
			f_closedir(currentDirectory_);
		}

		return *this;
	}

	// Post
	SDIterator operator++(int){
		SDIterator cpy = *this;
		++(*this);
		return cpy;
	}

	bool operator==(const SDIterator& rhs) { return currentEntry_ == rhs.currentEntry_; }
	bool operator!=(const SDIterator& rhs) { return currentEntry_ != rhs.currentEntry_; }

private:
	FILINFO* currentEntry_;
	DIR* currentDirectory_;
};

class SD : public IStorage{
public:
	SD();

	unsigned int WriteToFile(const char* fileName, uint8_t* buffer, uint32_t bufferLen);

	void AppendToFile(const char* fileName, uint8_t* buffer, uint32_t bufferLen);

	unsigned int ReadFromFile(const char* fileName, uint8_t* buffer, uint32_t maxReadLen);

	bool ReadLine(const char* fileName, uint8_t* buffer, uint32_t maxReadLen);
	void ResetRead();

	unsigned int GetNumberOfFilesInDir(const char* directory);

	inline bool IsDirectory(FILINFO& file) { return (file.fattrib & AM_DIR); }

	void CreateDirectory(const char* directory);

	void Initialize();
	void Deinitialize();

	/* Iterator stuff */
	void OpenDir(const char* dir);
	SDIterator begin();
	SDIterator end();

	// End should just return nullptr

	virtual ~SD();

private:
	FATFS hFatFs_; 		//Fatfs handle
	FIL hFile_; 		//File handle

	bool lineReading_;

	DIR iteratorDir_;
	FILINFO iteratorFile_;

};

} /* namespace Storage */

#endif /* INC_STORAGE_SD_H_ */
