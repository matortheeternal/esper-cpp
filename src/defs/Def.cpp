#include "Def.h"

namespace esper {

	Def::Def(DefinitionManager* manager, JsonValue& src, void* parent)
		: manager(manager), src(src), parent((Def*)parent) {}

	bool Def::hasSignature(const Signature& signature) {
		return false;
	}

	bool Def::hasPrimarySignature(const Signature& signature) {
		return false;
	}

	void Def::subrecordFound(Element* element, Subrecord* subrecord) {
		throw error("unimplemented");
	}

	uint8_t* Def::dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr) {
		throw error("unimplemented");
	}

	Element* Def::buildElement(Container* container) {
		throw error("unimplemented");
	}

	string Def::getName() {
		return src["name"].GetString();
	}

	string Def::getDefType() {
		throw error("unimplemented");
	}

	string Def::getSignature() {
		if (propertyIsUndefined(src, "signature")) return "";
		return src["signature"].GetString();
	}

	size_t Def::getSize() {
		if (src.HasMember("size")) return src["size"].GetUint();
		return 0;
	}
}