#pragma once

#include "MainRecord.h"

namespace esper {
	class MainRecordHeader : public Container {
	public:
		MainRecordHeader(MainRecord* record, Def* def)
		: Container(record, def) {}
	};
}