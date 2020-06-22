#pragma once
#include "FormatDef.h"

namespace esper {
	template<class T>
	class DivideDef : public FormatDef<T> {
	public:
		DivideDef(DefinitionManager* manager, JsonValue& src, Def* parent)
			: FormatDef<T>(manager, src, parent) {};
	};

	using UInt32DivideDef = DivideDef<uint32_t>;
	using UInt16DivideDef = DivideDef<uint16_t>;
	using UInt8DivideDef = DivideDef<uint8_t>;
	using Int32DivideDef = DivideDef<int32_t>;
	using Int16DivideDef = DivideDef<int16_t>;
	using Int8DivideDef = DivideDef<int8_t>;
}