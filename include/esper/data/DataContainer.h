#ifndef ESPER_DATA_CONTAINER_H_
#define ESPER_DATA_CONTAINER_H_

#include <string>

namespace esper {
	template<typename Type> string to_str(const Type& t) {
		ostringstream o;
		o << getData();
		return o.str();
	}

	class DataContainer {
	public:
		DataContainer() {}

		DataContainer(uint8_t* dataPtr)
			: dataPtr(dataPtr) {}

		void free() {
			std::free(dataPtr);
		}

		virtual string getValue() = 0;

		uint8_t* dataPtr;
	};
}

#endif