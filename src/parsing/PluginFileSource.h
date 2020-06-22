#pragma once

#include "../helpers/errors.h"
#include "MemoryMap.h"
#include "GroupHeader.h"
#include "RecordHeader.h"
#include "Subrecord.h"

namespace esper {
	class PluginFileSource : public MemoryMap {
	public:
		PluginFileSource(wstring filePath) : MemoryMap(filePath) {}

		RecordHeader* readRecordHeader() {
			if (dataPtr + sizeof(RecordHeader) > endPtr)
				throw error("Read out of bounds.");
			RecordHeader* result = reinterpret_cast<RecordHeader*>(dataPtr);
			dataPtr += sizeof(RecordHeader);
			return result;
		}

		GroupHeader* readGroupHeader() {
			if (dataPtr + sizeof(GroupHeader) > endPtr)
				throw error("Read out of bounds.");
			GroupHeader* result = reinterpret_cast<GroupHeader*>(dataPtr);
			dataPtr += sizeof(GroupHeader);
			return result;
		}

		vector<Subrecord*>* readSubrecords(RecordHeader* header) {
			vector<Subrecord*>* subrecords = new vector<Subrecord*>();
			const uint8_t* dataEndPtr = dataPtr + header->dataSize;
			while (dataPtr < dataEndPtr) {
				Subrecord* subrecord = reinterpret_cast<Subrecord*>(dataPtr);
				subrecords->push_back(subrecord);
				dataPtr += subrecord->totalSize();
			}
			return subrecords;
		}
	};
}