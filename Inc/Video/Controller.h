/*
 * Controller.h
 *
 *  Created on: 12 Nov 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_VIDEO_CONTROLLER_H_
#define INC_VIDEO_CONTROLLER_H_

#include <Storage/SD.h>
#include <Storage/Exceptions/SDExceptions.h>
#include <Compression/JPEG.h>
#include <Video/IVideoController.h>
#include <Video/Types.h>
#include <cstring>

namespace Video {

template<uint32_t Width, uint32_t Height, Compression::JPEGCompressor<Width,Height>& compressor, uint32_t BufferSize = 100>
class Controller : public IVideoController {
public:
	constexpr Controller(Storage::SD& storage) :
	storageHandler_(storage),
	compressionHandler_(compressor),
	imgCounter_(0){

		dirString_[0]=0;

	}

	void Initialize(){
		SetupDirectory();
	}

	void SetupDirectory()
	{
		/* Check what directory we should use */
		currentDir_ = GetDirNumber();

		// Make and save directory string
		sprintf(dirString_, "VIDEOS/%d", currentDir_);
	}

	void DoSave(){
		StoreVideoInformation(dirString_);
		StartNewDirectory();

		// reset vars
		saveSignal_ = false;
		imgCounter_ = 0;	// Reset image counter
	}

	void Save(){
		// TODO: make thread safe (mutex)
		saveSignal_ = true;
	}

	VideoInfoFile GetVideoInformation(uint32_t videoIdx)
	{
		if (videoIdx >= currentDir_) return k_nullFile;

		uVideoInfoFile tmpFileUnion;

		char fileString[64];
		sprintf(fileString, "VIDEOS/%lu/i.txt", videoIdx);

		try {
			storageHandler_.ReadFromFile(fileString, tmpFileUnion.raw, k_VideoInfoFileSize);
		} catch(...){
			return k_nullFile;
		}

		return tmpFileUnion.parsed;
	}

	void StoreVideoInformation(const char* directory)
	{
		/* Store information in struct */
		uVideoInfoFile fileUnion;
		fileUnion.parsed.startidx = imgCounter_ - 1;	// We havent actually saved imgCounter_ images yet

		// TODO: implement RTC and parse to date
		fileUnion.parsed.time.year = 0;
		fileUnion.parsed.time.month = 0;
		fileUnion.parsed.time.day = 0;
		fileUnion.parsed.time.hour = 0;
		fileUnion.parsed.time.minute = 0;

		fileUnion.parsed.size = GetVideoSize(currentDir_);
		fileUnion.parsed.n_images = GetImagesAmount(currentDir_);

		// Make filestring with the directory
		char fileString[64];
		sprintf(fileString, "%s/i.txt",directory);

		// Store on SD-Card
		try {
			storageHandler_.WriteToFile(fileString, fileUnion.raw, k_VideoInfoFileSize);
		} catch (...){
			// TODO: maybe try again? probably a filename issue
		}

	}

	void StartNewDirectory(){
		currentDir_ += 1;

		// Make and save directory string
		sprintf(dirString_, "VIDEOS/%d", currentDir_);
		storageHandler_.CreateDirectory(dirString_);
	}

	void Handle(uint8_t* src){

		/* Check if the directory string is setup correctly */
		if (dirString_[0]=='\0'){
			SetupDirectory();
			return;				// Discard in case it still isn't setup correctly
		}

		/* Compress the image */
		uint8_t* compressedFile = compressionHandler_.Compress(src);
		uint32_t fileSize = compressionHandler_.GetFileSize();

		/* Store image on SD-Card */
		if (fileSize>0){
			char fileName[64];
			sprintf(fileName,"%s/%d.jpg",dirString_, imgCounter_);
			try {
				storageHandler_.WriteToFile(fileName, compressedFile, fileSize);
			} catch (NoPathError& e){
				storageHandler_.CreateDirectory(dirString_);
			} catch (...){
				return;
			}
			IncrementImageCounter();
		}

		/* Check if a save has been requested */
		if (saveSignal_)
			DoSave();
	}

	inline void IncrementImageCounter(){
		/* Circular increment */
		imgCounter_ = (imgCounter_ + 1) % BufferSize;
	}

	uint32_t GetVideoSize(uint32_t vidIdx)
	{
		if (vidIdx > currentDir_) return 0xff;	// Error invalid index

		/* Loop through directory and sum file sizes */
		char dirString[64];
		uint32_t sum = 0;
		sprintf(dirString, "VIDEOS/%d",vidIdx);

		storageHandler_.OpenDir(dirString);
		for (Storage::SDIterator it = storageHandler_.begin(); it!=storageHandler_.end(); it++ ){
			// If its a file
			if (!storageHandler_.IsDirectory(*it)){
				/* Extract file size and sum*/
				sum += (*it).fsize;
			}
		}

		return sum;
	}

	uint32_t GetImagesAmount(uint32_t vidIdx)
	{
		if (vidIdx > currentDir_) return 0;	// Error invalid index

		/* Loop through directory and sum file sizes */
		char dirString[64];
		uint32_t sum = 0;
		sprintf(dirString, "VIDEOS/%d",vidIdx);

		storageHandler_.OpenDir(dirString);
		for (Storage::SDIterator it = storageHandler_.begin(); it!=storageHandler_.end(); it++ ){
			// If its a file
			if (!storageHandler_.IsDirectory(*it)){
				/* Extract file size and sum*/
				sum++;
			}
		}

		return sum;
	}

	inline uint8_t GetVideoAmount(){
		return GetDirNumber();
	}

	uint32_t GetDirNumber(){
		while(1){
			try {
				int n = 0;
				storageHandler_.OpenDir("VIDEOS");
				for (Storage::SDIterator it = storageHandler_.begin(); it!=storageHandler_.end(); it++ ){
					if (storageHandler_.IsDirectory(*it)){
						/* Extract dir number */
						int dirNumber = atoi(it->fname);
						n = n < dirNumber ? dirNumber : n;	// Only save largest number
					}
				}
				return n;
			} catch (NoPathError){
				/* Create directory */
				storageHandler_.CreateDirectory("VIDEOS");
				continue;	// attempt again
			}
		}
	}

	uint32_t GetStoredImage(uint32_t videoNumber, uint32_t imageNumber, uint8_t* buffer, uint32_t bufSize){
		try  {
			char fileName[64];
			sprintf(fileName,"VIDEOS/%d/%d.jpg", videoNumber, imageNumber);
			uint32_t read = storageHandler_.ReadFromFile(fileName, buffer, bufSize);
			return read;
		} catch (...){
			return 0;
		}
	}

	virtual ~Controller(){}

private:
	Storage::SD& storageHandler_;
	Compression::ICompressor& compressionHandler_;

	static constexpr uint32_t imgWidth = Width;
	static constexpr uint32_t imgHeight = Height;

	uint32_t imgCounter_;
	char dirString_[32];
	uint32_t currentDir_;

	bool saveSignal_;

};

} /* namespace Video */

#endif /* INC_VIDEO_CONTROLLER_H_ */
