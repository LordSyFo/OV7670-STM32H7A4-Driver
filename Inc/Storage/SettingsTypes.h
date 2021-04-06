/*
 * SettingsTypes.h
 *
 *  Created on: 4 Nov 2020
 *      Author: SYFO
 */

#ifndef INC_STORAGE_SETTINGSTYPES_H_
#define INC_STORAGE_SETTINGSTYPES_H_

#include <stdint.h>

constexpr unsigned int k_UserIDSize = 28;	// Without terminating null

typedef struct UserSettings {
	uint8_t parkingSensor;
	uint8_t suddenBreakAlert;
	uint8_t roadStripAlert;
	uint8_t alertVolume;
} __attribute__((__packed__)) UserSettings_t;

union UserSettingsUnion {
	UserSettings settings;
	uint8_t raw[sizeof(UserSettings)];
};

constexpr unsigned int k_MaxSettingNumber = sizeof(UserSettings);

typedef struct SettingFile {
	uint8_t userid[k_UserIDSize];
	uint8_t version[3];
	UserSettings_t userSettings;
} __attribute__((__packed__)) SettingFile_t;

constexpr unsigned int k_SettingFileSize = sizeof(SettingFile);

union SettingFileUnion {
	SettingFile settingFile;
	uint8_t raw[k_SettingFileSize];
};

constexpr UserSettings k_FactorySettings = {
	1,		// Parking sensor
	1,		// Sudden break alert
	1,		// Road strip alert
	255		// Alert volume
};

#endif /* INC_STORAGE_SETTINGSTYPES_H_ */
