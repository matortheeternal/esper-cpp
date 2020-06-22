#pragma once
#include "../../helpers/strings.h"
#include "ValueDef.h"
#include "../formats/FormatDef.h"
#include "../../data/UserIntData.h"
#include "../../elements/ValueElement.h"

namespace esper {
	template<class T>
	class IntegerDef : public ValueDef {
	public:
		IntegerDef(DefinitionManager* manager, JsonValue& src, void* parent)
			: ValueDef(manager, src, parent) {
			if (!src.HasMember("format")) return;
			formatDef = (FormatDef<T>*) manager->buildDef(src["format"], this);
		}

		virtual DataContainer* loadData(uint8_t* dataPtr) {
			return new IntData<T>(dataPtr);
		}
		
		string getValue(ValueElement* element) {
			return formatDef != nullptr
				? formatDef->dataToValue(element, getData(element))
				: getData(element)->toString();
		}

		void setValue(ValueElement* element, string value) {
			DataContainer* data = formatDef != nullptr
				? formatDef->valueToData(element, value)
				: new UserIntData<T>(value);
			element->setData(data);
		}

		size_t getSize() {
			return sizeof(T);
		}

		FormatDef<T>* formatDef;
	};
}