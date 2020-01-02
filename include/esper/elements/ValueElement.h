#ifndef ESPER_VALUEELEMENT_H
#define ESPER_VALUEELEMENT_H

#include "Element.h"
#include "../parsing/Subrecord.h"
#include "../data/DataContainer.h"

namespace esper {
	class ValueElement : public Element {
	public:
		ValueElement(Container* container, ValueDef* def)
			: Element(container, def) {
			data = static_cast<uint8_t*>(malloc(def->getSize()));
		}

		ValueElement(Container* container, ValueDef* def, Subrecord* subrecord)
			: Element(container, def) {
			size_t defSize = def->getSize();
			if (defSize > 0 && defSize != subrecord->size)
				throw error("Subrecord size does not match def size.");
			this->subrecord = subrecord;
		}

		uint8_t* getDataPtr() {
			if (data != nullptr) return data;
			return subrecord->getData();
		}

		DataContainer* getData() {
			return ((ValueDef*)def)->getData(this);
		}

		virtual string getValue() {};
		virtual void setValue(string value) {};

		Subrecord* subrecord = nullptr;
		uint8_t* data = nullptr;
	};
}

#endif