#pragma once
#include <cstdint>
#include "DataContainer.h"
#include "../helpers/strings.h"

namespace esper {
	template<class T>
	class IntData : public DataContainer {
	public:
		IntData() {}

		IntData(uint8_t* dataPtr) : DataContainer(dataPtr) {}

		T getData() {
			return *reinterpret_cast<T*>(dataPtr);
		}

		string toString() {
			return to_str<T>(getData());
		}
	};
}