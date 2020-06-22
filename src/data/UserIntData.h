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


	using UserUInt8 = UserIntData<uint8_t>;
	using UserUInt16 = UserIntData<uint16_t>;
	using UserUInt32 = UserIntData<uint32_t>;
	using UserInt8 = UserIntData<int8_t>;
	using UserInt16 = UserIntData<int16_t>;
	using UserInt32 = UserIntData<int32_t>;
}