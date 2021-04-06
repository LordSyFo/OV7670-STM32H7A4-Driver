/*
 * SettingsManager.h
 *
 *  Created on: 4 Nov 2020
 *      Author: SYFO
 */

#ifndef INC_STORAGE_SETTINGSMANAGER_H_
#define INC_STORAGE_SETTINGSMANAGER_H_

#include <Storage/SettingsTypes.h>
#include <Storage/IStorage.h>

namespace Storage {

// 2LQPKB0ESzTIWfN44rsW29L4HLK2 - Example of UserID

class SettingsManager {
public:
	SettingsManager(IStorage& storageHandler);

	void WriteSettings(char* userID, UserSettings_t settings);
	UserSettings_t ReadSettings(char* userID);

	unsigned int AppendToUserIDLookup(char* userID);

	unsigned int GetSettingsFileNumber(char* userID) noexcept;

	virtual ~SettingsManager();
private:
	IStorage& storageHandler_;
};

} /* namespace Storage */

#endif /* INC_STORAGE_SETTINGSMANAGER_H_ */
