#include "RecordManager.h"

namespace esper {
	MainRecord* RecordManager::getRecordByFormId(uint32_t formId) {
		return nullptr; // TODO
	};

	MainRecord* RecordManager::getRecordByLocalFormId(uint32_t localFormId) {
		return localRecordsByFormId->find(localFormId);
	};
}