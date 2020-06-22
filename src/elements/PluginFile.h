#pragma once

#include <cstdint>
#include <string>
#include "../parsing/PluginFileSource.h"
#include "../setup/Session.h"
#include "../setup/PluginSlot.h"
#include "../helpers/filesystem.h"
#include "Container.h"
#include "MainRecord.h"
#include "./interfaces/MasterManager.h"
#include "./interfaces/RecordManager.h"

namespace esper {
	using namespace std;

	struct PluginFileOptions {
		bool temporary;
	};

	class PluginFile : public Container, public MasterManager, public RecordManager {
	public:
		PluginFile(
			Session* session, 
			wstring filename, 
			PluginFileOptions options = PluginFileOptions()
		);

		void load(wstring filePath);
		void loadFileHeader();
		void loadGroups();
		bool isEsl();
		bool isDummy();
		PluginFile* getFile();

		Session* session;
		PluginFileOptions options;
		wstring filename;
		wstring filePath;
		MainRecord* header = nullptr;
		PluginFileSource* source = nullptr;
		PluginSlot* pluginSlot = nullptr;
	};
}