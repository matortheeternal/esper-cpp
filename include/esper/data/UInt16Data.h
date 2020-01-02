#ifndef ESPER_UINT16_DATA_H_
#define ESPER_UINT16_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class UInt16Data : public DataContainer {
	public:
		uint16_t getData() {
			return *reinterpret_cast<uint16_t*>(dataPtr);
		}

		std::string getValue() {
			return to_str(getData());
		}
	};
}

#endif