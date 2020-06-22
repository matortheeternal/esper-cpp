#include "ArrayDef.h"
#include "../elements/ArrayElement.h"

namespace esper {
	ArrayDef::ArrayDef(DefinitionManager* manager, JsonValue& src, void* parent)
		: MaybeSubrecordDef(manager, src, parent) {
		if (propertyIsUndefined(src, "element"))
			throw new error("Expected def property 'element' to be present.");
		elementDef = (Def*)manager->buildDef(src["element"]);
	}

	Element* ArrayDef::buildElement(Container* container) {
		return new ArrayElement(container, (Def*)this);
	}

	uint8_t* ArrayDef::dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr) {
		ArrayElement* container = dynamic_cast<ArrayElement*>(element);
		uint8_t* curPtr = dataPtr;
		while (curPtr < endPtr) {
			Element* childElement = elementDef->buildElement(container);
			curPtr = elementDef->dataFound(childElement, curPtr, endPtr);
		}
		return curPtr;
	}
}