#pragma once
#include "FormIdData.h"

namespace esper {
	size_t formIDSize = 4;

	class UserFormIdData : public FormIdData {
	public:
		UserFormIdData(const string& value) {
			parseBytes(value, dataPtr, formIDSize);
		}

		UserFormIdData(PluginFile* file, uint32_t localFormId);

		~UserFormIdData() {
			free(dataPtr);
		}
	};
}