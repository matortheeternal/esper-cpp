#ifndef ESPER_GROUP_HEADER_H_
#define ESPER_GROUP_HEADER_H_

#include <cstdint>
#include "signature.h"

namespace esper {
	struct GroupHeader {
		Signature signature;
		uint32_t groupSize;
		uint8_t label[4];
		int32_t groupType;
		uint8_t versionControlInfo[4];
		uint32_t unknown;
	};
}

#endif