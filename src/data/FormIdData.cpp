#include "FormIdData.h"
#include "../elements/MainRecord.h"
#include "../elements/PluginFile.h"

namespace esper {
	uint32_t FormIdData::toFileFormId(PluginFile* file) {
		auto ordinal = file->fileToOrdinal(this->file);
		if (ordinal == -1)
			throw MissingMasterError(file, this->file);
		return ordinal * 0x1000000 + getLocalFormId();
	}

	string FormIdData::toString() {
		return "{" + 
			wstringToString(file->filename) + 
			":" + 
			intToHex(getLocalFormId(), 6) + 
		"}";
	}

	MainRecord* FormIdData::resolveRecord() {
		return file->getRecordByFormId(this);
	}
}