#include "PluginFile.h"
#include "GroupRecord.h"

namespace esper {
	PluginFile::PluginFile(Session* session, wstring filename, PluginFileOptions options)
		: Container(nullptr, nullptr), MasterManager(), RecordManager(),
		session(session), 
		filename(filename), 
		options(options),
		filePath(L"") 
	{
		this->file = this;
		if (!options.temporary) session->pluginManager->addFile(this);
	}

	void PluginFile::load(wstring filePath) {
		assertFileExists(filePath);
		this->filePath = filePath;
		source = new PluginFileSource(filePath);
		loadFileHeader();
		loadGroups();
	}

	void PluginFile::loadFileHeader() {
		Def* fileHeaderDef = (Def*) session->definitionManager->getFileHeaderDef();
		header = MainRecord::build(this, "TES4");
		initMasters();
		initMasterIndexes();
	}

	void PluginFile::loadGroups() {
		while (source->match(GRUP_MARKER, 4))
			GroupRecord::load(this, GroupType::Top);
	}

	bool PluginFile::isEsl() {
		return false;
	}

	bool PluginFile::isDummy() {
		return filePath.length() == 0;
	}

	PluginFile* PluginFile::getFile() {
		return this;
	}
}