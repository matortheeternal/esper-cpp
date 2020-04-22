#pragma once
#include "MembersDef.h"

namespace esper {
	class MainRecordDef : public MembersDef {
	public:
		MainRecordDef(DefinitionManager* manager, JsonValue& src, Def* parent)
			: MembersDef(manager, src, parent) {}
	};
}