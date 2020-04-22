#pragma once
#include "FloatData.h"

namespace esper {
	class UserFloatData : public FloatData {
	public:
		UserFloatData(const string& value) {
			dataPtr = reinterpret_cast<uint8_t*>(new float);
			*dataPtr = parseFloat(value);
		}

		UserFloatData(const float& data) {
			dataPtr = reinterpret_cast<uint8_t*>(new float);
			*dataPtr = data;
		}

		~UserFloatData() {
			free(dataPtr);
		}
	};
}