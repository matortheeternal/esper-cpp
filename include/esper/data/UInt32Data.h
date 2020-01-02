#ifndef ESPER_UINT16_DATA_H_
#define ESPER_UINT16_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class UInt32Data : public DataContainer {
	public:
		UInt32Data(uint8_t* dataPtr) {
			data = *reinterpret_cast<uint32_t*>(dataPtr);
		}

		uint32_t data;
	};
}

#endif