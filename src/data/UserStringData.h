#pragma once
#include "StringData.h"

namespace esper {
	class UserStringData : public StringData {
	public:
		UserStringData(const string& value) {
			dataPtr = reinterpret_cast<uint8_t*>(new char[value.size()]);
			memcpy(dataPtr, value.c_str(), value.size());
		}

		~UserStringData() {
			free(dataPtr);
		}
	};
}