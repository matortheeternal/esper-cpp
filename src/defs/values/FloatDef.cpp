#include "FloatDef.h"
#include "../../elements/ValueElement.h"
#include "../../data/FloatData.h"
#include "../../data/UserFloatData.h"

namespace esper {
	DataContainer* FloatDef::loadData(uint8_t* dataPtr) {
		return new FloatData(dataPtr);
	}

	void FloatDef::setValue(ValueElement* element, string value) {
		element->setData(new UserFloatData(value));
	}
}