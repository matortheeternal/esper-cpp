#include "UserFormIdData.h"

namespace esper {
	UserFormIdData::UserFormIdData(PluginFile* file, uint32_t localFormId) {
		this->file = file;
		dataPtr = reinterpret_cast<uint8_t*>(new uint32_t);
		*dataPtr = localFormId;
	}
}
