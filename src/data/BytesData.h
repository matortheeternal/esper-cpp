#ifndef ESPER_BYTES_DATA_H_
#define ESPER_BYTES_DATA_H_

#include "DataContainer.h"
#include "../helpers/strings.h"

namespace esper {
	using namespace std;

	class BytesData : public DataContainer {
	public:
		BytesData() {}

		BytesData(uint8_t* dataPtr, size_t size)
		: DataContainer(dataPtr), size(size) {}

		uint8_t operator[](const unsigned int index) {
			if (index >= size) throw error("Index out of bounds.");
			return dataPtr[index];
		}

		uint8_t* getData() {
			return dataPtr;
		}

		string toString() {
			return formatBytes(dataPtr, size);
		}

		size_t size;
	};
}

#endif