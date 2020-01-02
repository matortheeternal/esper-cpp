#ifndef ESPER_FLOAT_DATA_H_
#define ESPER_FLOAT_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class FloatData : public DataContainer {
	public:
		FloatData(uint8_t* dataPtr) {
			data = *reinterpret_cast<float*>(dataPtr);
		}

		float data;
	};
}

#endif