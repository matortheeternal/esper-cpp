#ifndef ESPER_FLOAT_DATA_H_
#define ESPER_FLOAT_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class FloatData : public DataContainer {
	public:
		float getData() {
			return *reinterpret_cast<float*>(dataPtr);
		}

		std::string getValue() {
			return to_str(getData());
		}
	};
}

#endif