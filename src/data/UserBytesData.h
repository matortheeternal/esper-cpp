#pragma once
#include "BytesData.h"

namespace esper {
	class UserBytesData : public BytesData {
	public:
		UserBytesData(const string& value) : BytesData() {
			parseBytes(value, dataPtr, size);
		}

		~UserBytesData() {
			free(dataPtr);
		}
	};
}