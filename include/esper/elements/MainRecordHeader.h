#include "MainRecord.h"

class MainRecordHeader : public Container {
public:
	MainRecordHeader(MainRecord* record, Def* def)
	: Container(record, def) {

	}
};