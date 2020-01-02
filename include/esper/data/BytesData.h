#ifndef ESPER_BYTES_DATA_H_
#define ESPER_BYTES_DATA_H_

#include "DataContainer.h"

namespace esper {
	using namespace std;

	class BytesData : public DataContainer {
	public:
		BytesData(uint8_t* dataPtr, size_t size)
		: bytes(dataPtr), size(size) {}

		BytesData(const string& value) {
			parseBytes(value, bytes, size);
		}

		uint8_t operator[](const unsigned int index) {
			if (index >= size) throw error("Index out of bounds.");
			return bytes[index];
		}

		string toString() {
			return formatBytes(bytes, size);
		}

		uint8_t* bytes;
		size_t size;
	};
}

#endif