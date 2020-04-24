#pragma once
#include "FormatDef.h"

namespace esper {
	template<class T>
	class FlagsDef : public FormatDef<T> {
	public:
		FlagsDef(DefinitionManager* manager, JsonValue& src, Def* parent);

		virtual string getFlagValue(uint8_t index);
		virtual uint8_t getFlagIndex(string flag);
		virtual vector<string>* dataToArray(Element* element, DataContainer* data);
		virtual string dataToValue(Element* element, DataContainer* data);
		virtual DataContainer* valueToData(Element* element, string value);
		virtual JsonValue& getFlags();
	};
}