#include "../elements/Container.h"
#include "Def.h"

namespace esper {
	Element* Def::build(Container* container, Subrecord* subrecord) {
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