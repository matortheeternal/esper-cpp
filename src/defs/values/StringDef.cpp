#include "StringDef.h"
#include "../../data/StringData.h"
#include "../../data/UserStringData.h"
#include "../../elements/ValueElement.h"

namespace esper {
	DataContainer* StringDef::loadData(uint8_t* dataPtr) {
		return new StringData(dataPtr, getSize());
	}

	size_t StringDef::getSize() {
		return (*src)["size"].GetInt();
	}

	void StringDef::setValue(ValueElement* element, string value) {
		element->setData(new UserStringData(value));
	}

	string StringDef::defType = "string";
}