#include "FormIdData.h"
#include "../elements/MainRecord.h"
#include "../elements/PluginFile.h"

namespace esper {
	uint32_t FormIdData::toGlobalFormId() {
		// TODO
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