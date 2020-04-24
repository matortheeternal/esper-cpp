#ifndef ESPER_STRING_DATA_H_
#define ESPER_STRING_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	using namespace std;

	class StringData : public DataContainer {
	public:
		StringData() {}

		StringData(uint8_t* dataPtr, size_t size) 
		: DataContainer(dataPtr), size(size) {}

		string getData() {
			char* str = new char[size];
			memcpy(str, dataPtr, size);
			return string(str);
		}

		string toString() {
			return getData();
		}

		size_t size = 0;
	};
}

#endif