#pragma once
#include <vector>
#include "Element.h"
#include "../helpers/json.h"

namespace esper {
	class Container : public Element {
	public:
		Container(Container* container = nullptr, Def* def = nullptr)
			: Element(container, def) {}

		void initElements(const size_t targetSize = 0);
		void elementAdded(Element* element);
		virtual bool sorted();

		vector<Element*>* elements;
	};
}