#include "MasterManager.h"
#include "../PluginFile.h"
#include "../../resolution/elementResolution.h"

namespace esper {
	using namespace ElementResolution;

	void MasterManager::initMasters() {
		PluginFile* file = getFile();
		Element* masterFilesElement = getElement(file->header, "Master Files");
		PluginManager* manager = file->session->pluginManager;
		if (masterFilesElement == nullptr) return;
		for (Element* element : getElements(masterFilesElement)) {
			string filename = getData(element, 'MAST');
			masters->push_back(manager->getFileByName(filename, true));
		}
		userMasters->assign(masters->begin(), masters->end());
	};

	void MasterManager::initMasterIndexes() {

	};

	void MasterManager::updateMastersElement() {

	};

	PluginFile* MasterManager::ordinalToFile(uint8_t ordinal) {

	};

	int16_t MasterManager::fileToOrdinal(PluginFile* file) {

	};

	bool MasterManager::hasMaster(PluginFile* file) {

	};

	void MasterManager::addMaster(PluginFile* file) {

	};

	void MasterManager::removeMaster(PluginFile* file) {

	};

	ReferenceMap MasterManager::getMasterReferences() {

	};

	ReferenceCountMap MasterManager::countMasterReferences() {

	};

	vector<string> MasterManager::getUnusedMasters() {

	};

	void MasterManager::removeUnusedMasters() {

	};

	vector<PluginFile*> MasterManager::getMasters() {
		return vector<PluginFile*>(*userMasters);
	};

	vector<string> MasterManager::getMasterFilenames() {

	};
}