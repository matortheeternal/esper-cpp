#include "StructDef.h"
#include "../elements/StructElement.h"

namespace esper {
	StructDef::StructDef(DefinitionManager* manager, JsonValue& src, void* parent)
		: MaybeSubrecordDef(manager, src, parent) {
		if (!src.HasMember("elements"))
			throw error("Expected def property elements.");
		this->elementDefs = manager->buildDefs(src["elements"], this);
	}

	Element* StructDef::buildElement(Container* container) {
		return new StructElement(container, (Def*)this);
	}

	uint8_t* StructDef::dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr) {
		StructElement* structElement = dynamic_cast<StructElement*>(element);
		for (auto i = 0; i < elementDefs->size(); i++) {
			Def* def = (Def*)(*elementDefs)[i];
			Element* element = def->buildElement(structElement);
			dataPtr = def->dataFound(element, dataPtr, endPtr);
		}
		return dataPtr;
	}

	Def* StructDef::getElementDef(Subrecord* subrecord) {
		for (auto i = 0; i < elementDefs->size(); i++) {
			Def* def = (Def*)(*elementDefs)[i];
			if (def->hasSignature(subrecord->signature))
				return def;
		}
	}
}