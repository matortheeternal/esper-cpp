#pragma once
#include <cstdint>
#include "signature.h"

struct GroupHeader {
	Signature signature;
	uint32_t groupSize;
	uint8_t label[4];
	int32_t groupType;
	uint8_t versionControlInfo[4];
	uint32_t unknown;
};