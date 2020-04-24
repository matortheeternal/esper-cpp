#pragma once
#include "FormatDef.h"

namespace esper {
	template<class T>
	class DivideDef : public FormatDef<T> {
	public:
		DivideDef(DefinitionManager* manager, JsonValue& src, Def* parent)
			: FormatDef<T>(manager, src, parent) {};
	};
}