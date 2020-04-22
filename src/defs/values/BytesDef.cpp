#include "BytesDef.h"
#include "../../data/UserBytesData.h"
#include "../../elements/ValueElement.h"

namespace esper {
	DataContainer* BytesDef::loadData(uint8_t* dataPtr) {
		return new BytesData(dataPtr, getSize());
	}

	size_t BytesDef::getSize() {
		return src["size"].GetInt();
	}

	void BytesDef::setValue(ValueElement* element, string value) {
		element->setData(new UserBytesData(value));
	}

	string BytesDef::defType = "bytes";
}