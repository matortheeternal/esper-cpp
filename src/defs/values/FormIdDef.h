#pragma once
#include "IntegerDef.h"

namespace esper {
	class FormIdDef : public IntegerDef<uint32_t> {
	public:
		FormIdDef(DefinitionManager* manager, JsonValue& src, void* parent)
			: IntegerDef<uint32_t>(manager, src, parent) {
			if (src.HasMember("format")) 
				throw error("FormIdDef cannot have format.");
		};


	};
}