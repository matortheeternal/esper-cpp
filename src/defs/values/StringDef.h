#pragma once
#include "ValueDef.h"
#include "../../parsing/Subrecord.h"
#include "../../data/DataContainer.h"
#include "../../data/BytesData.h"
#include "../../setup/DefinitionManager.h"
#include "../../helpers/json.h"

namespace esper {
	class StringDef : public ValueDef {
	public:
		StringDef(DefinitionManager* manager, JsonValue& src, void* parent)
			: ValueDef(manager, src, parent) {
			if (propertyIsUndefined(src, "size")) src["size"].SetInt(0);
			if (!propertyIsPositiveIntOrZero(&src, "size"))
				throw DefSourceError("Def source has invalid size: ", src);
		}

		string getDefType() {
			return "string";
		}

		DataContainer* loadData(uint8_t* dataPtr);
		size_t getSize();
		void setValue(ValueElement* element, string value);
	};
}