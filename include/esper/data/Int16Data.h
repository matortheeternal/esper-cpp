#ifndef ESPER_INT16_DATA_H_
#define ESPER_INT16_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class Int16Data : public DataContainer {
	public:
		Int16Data(uint8_t* dataPtr) {
			data = *reinterpret_cast<int16_t*>(dataPtr);
		}

		int16_t data;
	};
}

#endif