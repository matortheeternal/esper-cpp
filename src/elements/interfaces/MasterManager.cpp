#include "MasterManager.h"
#include "../PluginFile.h"
#include "../../resolution/methods.h"

namespace esper {
	using namespace PathResolution;

	Element* MasterManager::getMastersElement() {
		MainRecord* fileHeader = getFile()->header;
		if (fileHeader == nullptr) return nullptr;
		return getElement(fileHeader, "Master Files");
	};

	void MasterManager::initMasters() {
		Element* masterFilesElement = getMastersElement();
		if (masterFilesElement == nullptr) return;
		PluginManager* manager = getFile()->session->pluginManager;
		for (Element* element : getElements(masterFilesElement)) {
			wstring filename = stringToWString(getValue(element, "MAST"));
			masters->push_back(manager->getFileByName(filename, true));
		}
		userMasters->assign(masters->begin(), masters->end());
	};

	void MasterManager::initMasterIndexes() {
		uint16_t index = 0;
		for (auto& master : *masters)
			masterIndexes->emplace(master->filename, index++);
		for (auto& pair : *masterIndexes)
			userMasterIndexes->emplace(pair.first, pair.second);
	};

	void MasterManager::updateMastersElement() {
		Element* masterFilesElement = getMastersElement();
		if (masterFilesElement == nullptr) return;
		// TODO
	};

	PluginFile* MasterManager::ordinalToFile(uint8_t ordinal) {
		if (ordinal == masters->size()) return getFile();
		return masters->at(ordinal);
	};

	int16_t MasterManager::fileToOrdinal(PluginFile* file) {
		return masterIndexes->at(file->filename);
	};

	bool MasterManager::hasMaster(PluginFile* file) {
		for (auto& master : *userMasters)
			if (master == file) return true;
		return false;
	};

	void MasterManager::addMaster(PluginFile* file) {
		userMasters->push_back(file);
	};

	void MasterManager::removeMaster(PluginFile* file) {
		auto end = remove_if(
			userMasters->begin(), 
			userMasters->end(), 
			[](auto& plugin) {
				return plugin == file;
			}
		);

		userMasters->erase(end, userMasters->end());
	};

	ReferenceMap MasterManager::getMasterReferences() {
		// TODO
	};

	ReferenceCountMap MasterManager::countMasterReferences() {
		// TODO
	};

	vector<string> MasterManager::getUnusedMasters() {
		// TODO
	};

	void MasterManager::removeUnusedMasters() {
		// TODO
	};

	vector<PluginFile*> MasterManager::getMasters() {
		return vector<PluginFile*>(*userMasters);
	};

	vector<string> MasterManager::getMasterFilenames() {
		vector<string>* filenames = new vector<string>();
		for (auto& plugin : *userMasters)
			filenames->push_back(wstringToString(plugin->filename));
		return *filenames;
	};
}