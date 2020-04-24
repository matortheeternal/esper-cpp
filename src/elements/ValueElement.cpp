#include "ValueElement.h"
#include "MainRecord.h"
#include "../defs/values/ValueDef.h"

namespace esper {
	DataContainer* ValueElement::getData() {
		return ((ValueDef*)def)->getData(this);
	};

	void ValueElement::setData(DataContainer* data) {
		((ValueDef*)def)->setData(this, data);
	};

	string ValueElement::getValue() {
		return ((ValueDef*)def)->getValue(this);
	};

	void ValueElement::setValue(string value) {
		((ValueDef*)def)->setValue(this, value);
	};

	MainRecord* ValueElement::getReferencedRecord() {
		return ((ValueDef*)def)->getReferencedRecord(this);
	};
}