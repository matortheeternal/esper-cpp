#pragma once
#include "../Def.h"
#include "../../elements/Element.h"
#include "../../data/UserIntData.h"

namespace esper {
	template<class T>
	class FormatDef : public Def {
	public:
		FormatDef(DefinitionManager* manager, JsonValue& src, Def* parent)
			: Def(manager, src, parent) {};

		virtual string dataToValue(Element* element, DataContainer* data) {
			return data->toString();
		};

		virtual DataContainer* valueToData(Element* element, string value) {
			return new UserIntData<T>(value);
		};
	};
}