#pragma once
#include "setup/DefinitionManager.h"
#include "setup/Session.h"
#include "defs/values/BytesDef.h"
#include "defs/values/FloatDef.h"
#include "defs/values/IntegerDef.h"
#include "defs/values/StringDef.h"
#include "defs/values/Int0Def.h"
#include "defs/values/FormIdDef.h"

namespace esper {
	void initDefs() {
		// value defs
		registerDef<BytesDef>("bytes");
		registerDef<FloatDef>("float");
		registerDef<IntegerDef<uint8_t>>("uint8");
		registerDef<IntegerDef<uint16_t>>("uint16");
		registerDef<IntegerDef<uint32_t>>("uint32");
		registerDef<IntegerDef<int8_t>>("int8");
		registerDef<IntegerDef<int16_t>>("int16");
		registerDef<IntegerDef<int32_t>>("int32");
		registerDef<StringDef>("string");
		registerDef<Int0Def>("int0");
		registerDef<FormIdDef>("formId");
	}
};