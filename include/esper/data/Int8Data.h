#ifndef ESPER_INT8_DATA_H_
#define ESPER_INT8_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class Int8Data : public DataContainer {
	public:
		int8_t getData() {
			return *reinterpret_cast<int8_t*>(dataPtr);
		}

		std::string getValue() {
			return to_str(getData());
		}
	};
}

#endif