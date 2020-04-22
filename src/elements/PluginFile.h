#ifndef ESPER_PLUGIN_FILE_H_
#define ESPER_PLUGIN_FILE_H_

#include <cstdint>
#include <string>
#include "../parsing/PluginFileSource.h"
#include "../setup/Session.h"
#include "../helpers/filesystem.h"
#include "Container.h"

namespace esper {
	using namespace std;

	struct PluginFileOptions {
		bool temporary;
	};

	class PluginFile : public Container {
	public:
		PluginFile(Session* session, wstring filePath, PluginFileOptions options)
		: Container(nullptr, nullptr) {
			this->session = session;
			this->filePath = filePath;
			this->filename = getFileName(filePath);
			this->file = this;
			this->options = options;
			if (!options.temporary) session->pluginManager->addFile(this);
		}

		static PluginFile* load(Session* session, wstring filePath, PluginFileOptions options) {
			assertFileExists(filePath);
			PluginFile* plugin = new PluginFile(session, filePath, options);
			plugin->source = new PluginFileSource(filePath);
			plugin->loadFileHeader();
			plugin->loadGroups();
			return plugin;
		}

		static wstring* getMasterFilenames(Session* session, wstring filePath) {
			PluginFileOptions options = { true };
			PluginFile* plugin = new PluginFile(session, filePath, options);
			plugin->source = new PluginFileSource(filePath);
			plugin->loadFileHeader();
			wstring* masterFilenames = plugin->getMasterFilenames();
			delete plugin;
			return masterFilenames;
		}

		wstring* getMasterFilenames() {
			// TODO
		}

		void loadFileHeader() {

		}

		void loadGroups() {

		}

		bool isEsl() {
			return false;
		}

		MainRecord* header;
		Session* session;
		PluginFileOptions options;
		wstring filePath;
		wstring filename;
		PluginFile* file;
		PluginFileSource* source;
		PluginSlot* pluginSlot;
	};
}

#endif