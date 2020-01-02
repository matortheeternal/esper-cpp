#ifndef ESPER_INT8_DATA_H_
#define ESPER_INT8_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class Int8Data : public DataContainer {
	public:
		Int8Data(uint8_t* dataPtr) {
			data = *reinterpret_cast<int8_t*>(dataPtr);
		}

		int8_t data;
	};
}

#endif