#pragma once
#include "FormIdData.h"

namespace esper {
	class UserFormIdData : public FormIdData {
	public:
		UserFormIdData(const string& value) {
			// TODO
		}

		UserFormIdData(const PluginFile* file, uint32_t localFormId);

		~UserFormIdData() {
			free(dataPtr);
		}
	};
}