#ifndef ESPER_DATA_CONTAINER_H_
#define ESPER_DATA_CONTAINER_H_

#include <string>

namespace esper {
	using namespace std;

	template<typename Type> string to_str(const Type& t) {
		ostringstream o;
		o << t;
		return o.str();
	}

	class DataContainer {
	public:
		DataContainer() {}

		DataContainer(uint8_t* dataPtr)
			: dataPtr(dataPtr) {}

		virtual string toString() = 0;

		uint8_t* dataPtr;
	};
}

#endif