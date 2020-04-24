#pragma once
#include <vector>
#include <unordered_map>

namespace esper {
	using namespace std;

	class PluginFile;
	class MainRecord;
	class Element;

	using ReferenceMap = unordered_map<wstring, vector<MainRecord*>>;
	using ReferenceCountMap = unordered_map<wstring, uint32_t>;
	using FileList = vector<PluginFile*>;
	using IndexesMap = unordered_map<wstring, uint8_t>;

	class MasterManager {
	public:
		MasterManager() {}

		Element* getMastersElement();
		void initMasters();
		void initMasterIndexes();
		void updateMastersElement();
		PluginFile* ordinalToFile(uint8_t ordinal);
		int16_t fileToOrdinal(PluginFile* file);
		bool hasMaster(PluginFile* file);
		void addMaster(PluginFile* file);
		void removeMaster(PluginFile* file);
		ReferenceMap getMasterReferences();
		ReferenceCountMap countMasterReferences();
		vector<string> getUnusedMasters();
		void removeUnusedMasters();
		vector<PluginFile*> getMasters();
		vector<string> getMasterFilenames();
		virtual PluginFile* getFile() = 0;

		FileList* masters = new FileList();
		FileList* userMasters = new FileList();
		IndexesMap* masterIndexes = new IndexesMap();
		IndexesMap* userMasterIndexes = new IndexesMap();
	};
}