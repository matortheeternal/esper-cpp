#ifndef ESPER_STRING_DATA_H_
#define ESPER_STRING_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	using namespace std;

	class StringData : public DataContainer {
	public:
		StringData(uint8_t* dataPtr, size_t size) {
			data = (char*) dataPtr;
		}

		char* data;
	};
}

#endif