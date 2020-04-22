#ifndef ESPER_RECORD_HEADER_H_
#define ESPER_RECORD_HEADER_H_

#include "windows.h"
#include <cstdint>
#include "Signature.h"

namespace esper {
	struct RecordHeader {
		Signature signature;
		uint32_t dataSize;
		uint32_t flags;
		uint32_t formId;
		uint8_t versionControl1[4];
		uint8_t formVersion[2];
		uint8_t versionControl2[2];
	};
}

#endif