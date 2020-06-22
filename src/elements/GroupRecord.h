#pragma once
#include "Container.h"
#include "../parsing/GroupHeader.h"

namespace esper {
	const uint8_t GRUP_MARKER[4] = { 'G', 'R', 'U', 'P' };

	const enum class GroupType : int32_t {
		Top = 0,
		WorldChildren = 1,
		InteriorCellBlock = 2,
		InteriorCellSubBlock = 3,
		ExteriorCellBlock = 4,
		ExteriorCellSubBlock = 5,
		CellChildren = 6,
		TopicChildren = 7,
		CellPersistentChildren = 8,
		CellTemporaryChildren = 9
	};

	class GroupRecord : public Container {
	public:
		GroupRecord(Container* container);

		static GroupRecord* load(Container* container, GroupType expectedType);

		void loadGroupHeader();
		void loadRecords();
		string getLabelSignature();
		GroupType getChildGroupType();
		vector<string>* getAllowedRecordSignatures();

		GroupHeader* header = nullptr;
	};
}