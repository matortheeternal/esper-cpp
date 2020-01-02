#ifndef ESPER_INT16_DATA_H_
#define ESPER_INT16_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class Int16Data : public DataContainer {
	public:
		int16_t getData() {
			return *reinterpret_cast<int16_t*>(dataPtr);
		}

		std::string getValue() {
			return to_str(getData());
		}
	};
}

#endif