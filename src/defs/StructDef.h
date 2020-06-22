#pragma once
#include "MaybeSubrecordDef.h"

namespace esper {
	class StructDef : MaybeSubrecordDef {
	public:
		StructDef(DefinitionManager* manager, JsonValue& src, void* parent);

		string getDefType() {
			return "struct";
		}

		Element* buildElement(Container* container);
		uint8_t* dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr);
		Def* getElementDef(Subrecord* subrecord);

		vector<void*>* elementDefs;
	};
}