#ifndef ESPER_INT32_DATA_H_
#define ESPER_INT32_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class Int32Data : public DataContainer {
	public:
		Int32Data(uint8_t* dataPtr) {
			data = *reinterpret_cast<int32_t*>(dataPtr);
		}

		int32_t data;
	};
}

#endif