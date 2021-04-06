/*
 * Types.h
 *
 *  Created on: 13 Nov 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_VIDEO_TYPES_H_
#define INC_VIDEO_TYPES_H_

namespace Video {

typedef struct Timestamp {
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
} __attribute__((__packed__)) Timestamp;

typedef struct VideoInfoFile {
	uint32_t startidx;
	uint32_t size;
	uint32_t n_images;
	Timestamp time;
} __attribute__((__packed__)) VideoInfoFile;

constexpr uint32_t k_VideoInfoFileSize = sizeof(VideoInfoFile);

union uVideoInfoFile {
	uint8_t raw[k_VideoInfoFileSize];
	VideoInfoFile parsed;
};

constexpr VideoInfoFile k_nullFile = {
		0,
		0,
		0,
		0,
		0,
		0
};

}



#endif /* INC_VIDEO_TYPES_H_ */
