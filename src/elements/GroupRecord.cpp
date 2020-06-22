#include "GroupRecord.h"
#include "../parsing/GroupHeader.h"
#include "PluginFile.h"

namespace esper {
	using GroupTypeMap = unordered_map<string, GroupType>;

	const GroupTypeMap TopChildGroupTypes = {
		{ "WRLD", GroupType::WorldChildren },
		{ "CELL", GroupType::CellChildren },
		{ "DIAL", GroupType::TopicChildren }
	};

	GroupRecord::GroupRecord(Container* container)
		: Container(container, nullptr) {}

	GroupRecord* GroupRecord::load(Container* container, GroupType expectedType) {
		GroupRecord* group = new GroupRecord(container);
		group->loadGroupHeader();
		group->loadRecords();
		return group;
	}

	void GroupRecord::loadGroupHeader() {
		header = file->source->readGroupHeader();
	}

	void GroupRecord::loadRecords() {
		GroupType childGroupType = getChildGroupType();
		vector<string>* recordSignatures = getAllowedRecordSignatures();
		file->source->readMultiple(header->groupSize, [&]() {
			if (file->source->match(GRUP_MARKER, 4)) {
				GroupRecord::load(this, childGroupType);
			} else {
				MainRecord::build(this, recordSignatures);
			}
		});
	}

	string GroupRecord::getLabelSignature() {
		return string((char*)header->label);
	}

	GroupType GroupRecord::getChildGroupType() {
		if (header->groupType == (int32_t)GroupType::Top) {
			string labelSignature = getLabelSignature();
			auto& it = TopChildGroupTypes.find(labelSignature);
			if (it != TopChildGroupTypes.end()) return it->second;
			throw new error("Group does not support child groups.");
		} else {
			throw new error("TODO.");
		}
	}

	vector<string>* GroupRecord::getAllowedRecordSignatures() {
		return nullptr; // TODO
	}
}