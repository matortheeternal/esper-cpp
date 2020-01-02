#ifndef ESPER_INT32_DATA_H_
#define ESPER_INT32_DATA_H_

#include <cstdint>
#include "DataContainer.h"

namespace esper {
	class Int32Data : public DataContainer {
	public:
		int32_t getData() {
			return *reinterpret_cast<int32_t*>(dataPtr);
		}

		std::string getValue() {
			return to_str(getData());
		}
	};
}

#endif