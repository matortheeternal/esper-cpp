#include "ValueDef.h"
#include "../../elements/Element.h"
#include "../../elements/Container.h"
#include "../../elements/ValueElement.h"
#include "../../elements/MainRecord.h"

namespace esper {
	MainRecord* ValueDef::getReferencedRecord(Element* element) {
		throw error(element->getName() + " does not reference records.");
	}

	Element* ValueDef::build(Container* container) {
		return new ValueElement(container, this);
	}

	uint8_t* ValueDef::dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr) {
		ValueElement* valueElement = (ValueElement*)element;
		auto defSize = getSize();
		if (dataPtr + defSize > endPtr)
			throw error("Read out of bounds.");
		valueElement->data = loadData(dataPtr);
		return dataPtr + defSize;
	}

	DataContainer* ValueDef::getData(ValueElement* element) {
		return element->data;
	}

	void ValueDef::setData(ValueElement* element, DataContainer* data) {
		delete element->data;
		element->data = data;
		element->state.set(ElementState::modified);
	}

	string ValueDef::getValue(ValueElement* element) {
		return getData(element)->toString();
	}
}