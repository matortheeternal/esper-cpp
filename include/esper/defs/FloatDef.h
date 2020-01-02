#include "ValueDef.h"

class FloatDef : public ValueDef {
public:
	FloatDef(DefinitionManager* manager, JsonValue* src, Def* parent)
		: ValueDef(manager, src, parent) {
	}

	FloatElement* build(Element* container, Subrecord* subrecord) {
		FloatElement* element = new FloatElement(container, this);
		element->build(subrecord);
		return element;
	}

	size_t getSize() {
		return 4;
	}
};

string FloatDef::defType = "float";
registerDef<FloatDef>();