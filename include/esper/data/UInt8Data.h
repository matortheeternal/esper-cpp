#ifndef ESPER_UINT8_DATA_H_
#define ESPER_UINT8_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class UInt8Data : public DataContainer {
	public:
		uint8_t getData() {
			return *dataPtr;
		}

		std::string getValue() {
			return to_str(getData());
		}
	};
}

#endif