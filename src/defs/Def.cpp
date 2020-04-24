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

	Element* Def::build(Container* container) {
		throw error("unimplemented");
	}

	void Def::subrecordFound(Element* element, Subrecord* subrecord) {
		dataFound(element, subrecord->getData(), subrecord->getEnd());
	}

	uint8_t* Def::dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr) {
		throw error("unimplemented");
	}

	Element* Def::build(Container* container) {
		throw error("unimplemented");
	}

	string Def::getName() {
		return (*src)["name"].GetString();
	}

	size_t Def::getSize() {
		if (src->HasMember("size")) return (*src)["size"].GetUint();
		return 0;
	}
}