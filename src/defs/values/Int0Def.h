#pragma once
#include "ValueDef.h"

namespace esper {
	class Int0Def : public ValueDef {
	public:
		Int0Def(DefinitionManager* manager, JsonValue& src, void* parent)
			: ValueDef(manager, src, parent) {}

		DataContainer* loadData(uint8_t* dataPtr);
		void setValue(ValueElement* element, string value) {};

		size_t getSize() {
			return 0;
		}
	};
}