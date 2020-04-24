#pragma once

#include <cstdint>
#include "Signature.h"

namespace esper {
	class Subrecord {
	public:
		static size_t baseSize;

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

	size_t Subrecord::baseSize = 6;
}