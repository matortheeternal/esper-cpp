#include "StructDef.h"
#include "../elements/StructElement.h"

namespace esper {
	Element* StructDef::build(Container* container) {
		return new StructElement(container, (Def*)this);
	}

	void StructDef::subrecordFound(Element* element, Subrecord* subrecord) {
		dataFound(element, subrecord->getData(), subrecord->getEnd());
	}

	void StructDef::dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr) {
		StructElement* structElement = (StructElement*)element;
		for (auto i = 0; i < elementDefs->size(); i++) {
			Def* def = (Def*)(*elementDefs)[i];
			Element* element = def->build(structElement);
			dataPtr = def->dataFound(element, dataPtr, endPtr);
		}
	}

	Def* StructDef::getElementDef(Subrecord* subrecord) {
		for (auto i = 0; i < elementDefs->size(); i++) {
			Def* def = (Def*)(*elementDefs)[i];
			if (def->hasSignature(subrecord->signature))
				return def;
		}
	}

	string StructDef::defType = "struct";
}