#pragma once

#include "MaybeSubrecordDef.h"

namespace esper {
	class ArrayDef : public MaybeSubrecordDef {
	public:
		ArrayDef(DefinitionManager* manager, JsonValue& src, void* parent);

		Element* buildElement(Container* container);
		uint8_t* dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr);

		string getDefType() {
			return "array";
		}

		Def* elementDef = nullptr;
	};
}