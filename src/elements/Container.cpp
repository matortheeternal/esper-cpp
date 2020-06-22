#include "Container.h"
#include "../defs/Def.h"

namespace esper {
	void Container::initElements(const size_t targetSize) {
		elements = new vector<Element*>(targetSize);
	}

	void Container::elementAdded(Element* element) {
		if (ordered()) {
			elements->at(element->def->sortOrder) = element;
		} else {
			elements->push_back(element);
		}
	}

	bool Container::ordered() {
		return false;
	}
}