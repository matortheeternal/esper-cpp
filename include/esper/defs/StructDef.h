#include "MaybeSubrecordDef.h"

class StructDef : MaybeSubrecordDef {
public:
	StructDef(DefinitionManager* manager, JsonValue* src, Def* parent)
		: MaybeSubrecordDef(manager, src, parent) {
		if (!src->HasMember("elements")) throw error("Expected def property elements.");
		this->elementDefs = manager->buildDefs(src["elements"], this);
	}

	Def* elementDefs;
};

string StructDef::defType = "struct";
registerDef<StructDef>();