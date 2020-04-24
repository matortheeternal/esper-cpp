#pragma once
#include "FormatDef.h"

namespace esper {
	template<class T>
	class EnumDef : public FormatDef<T> {
	public:
		EnumDef(DefinitionManager* manager, JsonValue& src, Def* parent);

		virtual string dataToValue(Element* element, DataContainer* data);
		virtual DataContainer* valueToData(Element* element, string value);
		virtual JsonValue& getOptions();
	};
}