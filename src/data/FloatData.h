#pragma once
#include "DataContainer.h"
#include "../helpers/strings.h"

namespace esper {
	class FloatData : public DataContainer {
	public:
		FloatData() {}

		FloatData(uint8_t* dataPtr) : DataContainer(dataPtr) {}

		float getData() {
			return *reinterpret_cast<float*>(dataPtr);
		}

		std::string toString() {
			return to_str(getData());
		}
	};
}