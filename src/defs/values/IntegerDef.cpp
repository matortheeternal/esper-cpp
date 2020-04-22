#include "IntegerDef.h"
#include "../../elements/ValueElement.h"
#include "../../data/IntData.h"
#include "../../data/UserIntData.h"

namespace esper {
	template<class T>
	DataContainer* IntegerDef<T>::loadData(uint8_t* dataPtr) {
		return new IntData<T>(dataPtr);
	}

	template<class T>
	string IntegerDef<T>::getValue(ValueElement* element) {
		return formatDef != nullptr
			? formatDef->dataToValue(element, getData(element))
			: getData(element)->toString();
	}

	template<class T>
	void IntegerDef<T>::setValue(ValueElement* element, string value) {
		DataContainer* data = formatDef != nullptr
			? formatDef->valueToData(element, value)
			: new UserIntData<T>(value);
		element->setData(data);
	}

	string UInt8Def::defType = "uint8";
	string UInt16Def::defType = "uint16";
	string UInt16Def::defType = "uint32";
	string Int8Def::defType = "int8";
	string Int16Def::defType = "int16";
	string Int32Def::defType = "int32";
}