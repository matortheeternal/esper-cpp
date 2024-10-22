#pragma once
#include "ValueDef.h"
#include "../../parsing/Subrecord.h"

namespace esper {
	class Element;
	class ValueElement;

	class FloatDef : public ValueDef {
	public:
		FloatDef(DefinitionManager* manager, JsonValue& src, void* parent)
			: ValueDef(manager, src, parent) {}

		string getDefType() {
			return "float";
		}

		DataContainer* loadData(uint8_t* dataPtr);
		void setValue(ValueElement* element, string value);

		size_t getSize() {
			return 4;
		}
	};
}
