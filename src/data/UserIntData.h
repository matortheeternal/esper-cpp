#pragma once
#include "IntData.h"

namespace esper {
	template<class T>
	class UserIntData : public IntData<T> {
	public:
		UserIntData(const string& value) {
			dataPtr = reinterpret_cast<uint8_t*>(new T);
			*dataPtr = parseInt<T>(value);
		}

		UserIntData(const T& data) {
			dataPtr = reinterpret_cast<uint8_t*>(new T);
			*dataPtr = data;
		}

		~UserIntData() {
			free(dataPtr);
		}
	};
}