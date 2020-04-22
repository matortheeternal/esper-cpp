#pragma once
#include "setup/DefinitionManager.h"
#include "setup/Session.h"
#include "defs/BytesDef.h"
#include "defs/FloatDef.h"

namespace esper {
	void initDefs() {
		registerDef<BytesDef>("bytes");
		registerDef<FloatDef>("float");
	}
};