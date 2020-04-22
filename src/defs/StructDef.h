#pragma once
#include "MaybeSubrecordDef.h"

namespace esper {
	class StructDef : MaybeSubrecordDef {
	public:
		StructDef(DefinitionManager* manager, JsonValue& src, void* parent)
			: MaybeSubrecordDef(manager, src, parent) {
			if (!src->HasMember("elements")) 
				throw error("Expected def property elements.");
			this->elementDefs = manager->buildDefs((*src)["elements"], this);
		}

		Element* build(Container* container);
		void subrecordFound(Element* element, Subrecord* subrecord);
		void dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr);
		Def* getElementDef(Subrecord* subrecord);

		vector<void*>* elementDefs;
	};
}