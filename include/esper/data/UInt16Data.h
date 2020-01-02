#ifndef ESPER_UINT16_DATA_H_
#define ESPER_UINT16_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class UInt16Data : public DataContainer {
	public:
		UInt16Data(uint8_t* dataPtr) {
			data = *reinterpret_cast<uint16_t*>(dataPtr);
		}

		uint16_t data;
	};
}

#endif