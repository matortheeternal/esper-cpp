#pragma once

#include <cstdint>
#include "Signature.h"

namespace esper {
	class Subrecord {
	public:
		inline static size_t baseSize = 6;

		size_t totalSize() {
			return Subrecord::baseSize + size;
		}

		uint8_t* getData() {
			return reinterpret_cast<uint8_t*>(this) + baseSize;
		}

		uint8_t* getEnd() {
			return getData() + size;
		}

		Signature signature;
		uint16_t size;
	};
}