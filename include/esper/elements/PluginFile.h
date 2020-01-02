#pragma once
#include "windows.h"
#include "fileapi.h"
#include "memoryapi.h"
#include <vector>
#include <cstdint>
#include <exception>
#include <string>
#include "../parsing/PluginFileSource.h"
#include "Element.h"

namespace esper {
	using namespace std;

	struct PluginFileOptions {
		bool temporary;
	};

	class PluginFile : Element {
	public:
		PluginFile(Session* session, wstring _filePath, PluginFileOptions* options) {
			this->session = session;
			this->filePath = filePath;
			this->filename = getFileName(filePath);
			this->file = this;
			this->options = options;
			if (!options->temporary) session->pluginManager->addFile(this);
		}

		~PluginFile() {
			delete this->options;
		}

		static PluginFile load(Session* session, wstring filePath, PluginFileOptions options) {
			assertFileExists(filePath);
			PluginFile* plugin = new PluginFile(session, filePath, options);
			plugin->source = new PluginFileSource(filePath);
			plugin->loadFileHeader();
			plugin->loadGroups();
			return plugin;
		}

		static wstring* getMasterFilenames(Session* session, wstring filePath) {
			PluginFile* plugin = new PluginFile(session, filePath, new PluginFileOptions(true));
			plugin->source = new PluginFileSource(filePath);
			plugin->loadFileHeader();
			wstring* masterFileNames = plugin->getMasterFilenames();
			delete plugin;
			return masterFilenames;
		}

		wstring* getMasterFilenames() {
			// TODO
		}

		Session* session;
		PluginFileOptions* options;
		wstring filePath;
		wstring filename;
		PluginFile* file;
		PluginFileSource* source;
	};
}