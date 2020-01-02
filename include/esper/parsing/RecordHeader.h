#pragma once
#include "windows.h"
#include <cstdint>
#include "Signature.h"

struct RecordHeader {
	Signature signature;
	uint32_t dataSize;
	uint32_t flags;
	uint32_t formId;
	uint8_t versionControl1[4];
	uint8_t formVersion[2];
	uint8_t versionControl2[2];
};