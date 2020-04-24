#include "FormatDef.h"
#include "../../elements/Element.h"

namespace esper {
	string FormatDef<class T>::dataToValue(Element* element, DataContainer* data) {
		return data->toString();
	}

	DataContainer* FormatDef<class T>::valueToData(Element* element, string value) {
		return new UserIntData<T>(value);
	}
}