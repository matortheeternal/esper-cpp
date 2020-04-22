#pragma once
#include "IntegerDef.h"

namespace esper {
	class FormIdDef : public UInt32Def {
	public:
		FormIdDef(DefinitionManager* manager, JsonValue& src, Def* parent)
			: UInt32Def(manager, src, parent) {
			if (src.HasMember("format")) 
				throw error("FormIdDef cannot have format.");
		};


	};
}