#include "ValueElement.h"
#include "../defs/values/ValueDef.h"

namespace esper {
	DataContainer* ValueElement::getData() {
		return ((ValueDef*)def)->getData(this);
	}

	void ValueElement::setData(DataContainer* data) {
		((ValueDef*)def)->setData(this, data);
	}
}