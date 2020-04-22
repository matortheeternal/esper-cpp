#include "Container.h"
#include "Element.h"

namespace esper {
	void Container::initElements(const size_t targetSize = 0) {
		elements = new vector<Element*>(targetSize);
	}

	void Container::elementAdded(Element* element) {
		if (sorted()) {
			(*elements)[element->def->sortOrder] = element;
		} else {
			elements->push_back(element);
		}
	}

	bool Container::sorted() {
		return false;
	}
}