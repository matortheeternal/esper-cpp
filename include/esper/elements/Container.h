#include "Element.h"
#include "../helpers/json.h"
#include <vector>

class Container : public Element {
public:
	Container(Element* container = nullptr, Def* def = nullptr)
	: Element(container, def) {
	}

	void initElements(const size_t targetSize = 0) {
		elements = new vector<Element*>();
		if (targetSize > 0) elements->reserve(targetSize);
	}

	void elementAdded(Element* element) {
		if (sorted()) {
			elements[element->def->sortOrder] = element;
		} else {
			elements->push_back(element);
		}
	}

	virtual bool sorted() {
		return false;
	}

	vector<Element*>* elements;
};