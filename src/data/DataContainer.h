#pragma once
#include <string>

namespace esper {
	using namespace std;

	class DataContainer {
	public:
		DataContainer() {}

		DataContainer(uint8_t* dataPtr)
			: dataPtr(dataPtr) {}

		virtual string toString() = 0;

		uint8_t* dataPtr = nullptr;
	};
}