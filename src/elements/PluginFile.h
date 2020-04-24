#pragma once

#include <cstdint>
#include <string>
#include "../parsing/PluginFileSource.h"
#include "../setup/Session.h"
#include "../helpers/filesystem.h"
#include "Container.h"
#include "MainRecord.h"
#include "./interfaces/MasterManager.h"

namespace esper {
	using namespace std;

	struct PluginFileOptions {
		bool temporary;
	};

	class PluginFile : public Container, public MasterManager {
	public:
		PluginFile(Session* session, wstring filename);

		PluginFile(Session* session, wstring filePath, PluginFileOptions options);

		static PluginFile* load(Session* session, wstring filePath, PluginFileOptions options);
		static wstring* getMasterFilenames(Session* session, wstring filePath);
		
		void loadFileHeader();
		void loadGroups();
		bool isEsl();
		bool isDummy();
		PluginFile* getFile();

		MainRecord* header;
		Session* session;
		PluginFileOptions options;
		wstring filePath;
		wstring filename;
		PluginFileSource* source;
		PluginSlot* pluginSlot;
	};
}