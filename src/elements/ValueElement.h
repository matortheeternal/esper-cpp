#pragma once
#include "Element.h"
#include "Container.h"
#include "../parsing/Subrecord.h"
#include "../data/DataContainer.h"
#include "../flags/ElementState.h"

namespace esper {
	class ValueElement : public Element {
	public:
		ValueElement(Container* container, ValueDef* def)
			: Element(container, (Def*)def) {}

		DataContainer* getData();
		void setData(DataContainer* data);

		virtual string getValue() {};
		virtual void setValue(string value) {};

		DataContainer* data = nullptr;
		ElementState flags = ElementState();
	};
}