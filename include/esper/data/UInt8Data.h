#ifndef ESPER_UINT8_DATA_H_
#define ESPER_UINT8_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class UInt8Data : public DataContainer {
	public:
		UInt8Data(uint8_t* dataPtr) {
			data = *dataPtr;
		}

		uint8_t data;
	};
}

#endif