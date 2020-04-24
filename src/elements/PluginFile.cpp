#include "PluginFile.h"

namespace esper {
	PluginFile::PluginFile(Session* session, wstring filename)
		: Container(nullptr, nullptr) {
		this->session = session;
		this->filePath = L"";
		this->filename = filename;
		this->file = this;
		this->options = PluginFileOptions();
	}

	PluginFile::PluginFile(Session* session, wstring filePath, PluginFileOptions options) :
		Container(nullptr, nullptr) {
		this->session = session;
		this->filePath = filePath;
		this->filename = getFileName(filePath);
		this->file = this;
		this->options = options;
		if (!options.temporary) session->pluginManager->addFile(this);
	}

	PluginFile* PluginFile::load(Session* session, wstring filePath, PluginFileOptions options) {
		assertFileExists(filePath);
		PluginFile* plugin = new PluginFile(session, filePath, options);
		plugin->source = new PluginFileSource(filePath);
		plugin->loadFileHeader();
		plugin->loadGroups();
		return plugin;
	}

	wstring* PluginFile::getMasterFilenames(Session* session, wstring filePath) {
		PluginFileOptions options = { true };
		PluginFile* plugin = new PluginFile(session, filePath, options);
		plugin->source = new PluginFileSource(filePath);
		plugin->loadFileHeader();
		wstring* masterFilenames = plugin->getMasterFilenames();
		delete plugin;
		return masterFilenames;
	}

	void PluginFile::loadFileHeader() {

	}

	void PluginFile::loadGroups() {

	}

	bool PluginFile::isEsl() {
		return false;
	}

	bool PluginFile::isDummy() {
		return filePath.length == 0;
	}

	PluginFile* PluginFile::getFile() {
		return this->file;
	}
}