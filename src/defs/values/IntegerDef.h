#pragma once
#include "ValueDef.h"
#include "../FormatDef.h"

namespace esper {
	template<class T>
	class IntegerDef : public ValueDef {
	public:
		IntegerDef(DefinitionManager* manager, JsonValue& src, Def* parent)
			: ValueDef(manager, src, parent) {
			if (!src.HasMember("format")) return;
			formatDef = (FormatDef<T>*) manager->buildDef(src["format"], this);
		}

		DataContainer* loadData(uint8_t* dataPtr);
		void setValue(ValueElement* element, string value);
		string IntegerDef::getValue(ValueElement* element);

		size_t getSize() {
			return sizeof(T);
		}

		FormatDef<T>* formatDef;
	};

	using UInt8Def = IntegerDef<uint8_t>;
	using UInt16Def = IntegerDef<uint16_t>;
	using UInt32Def = IntegerDef<uint32_t>;
	using Int8Def = IntegerDef<int8_t>;
	using Int16Def = IntegerDef<int16_t>;
	using Int32Def = IntegerDef<int32_t>;
}