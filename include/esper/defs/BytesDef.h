#include "ValueDef.h"
#include "../setup/DefinitionManager.h"
#include "../helpers/helpers.h"
#include "../data/BytesData.h"

namespace esper {
	class BytesDef : public ValueDef {
	public:
		BytesDef(DefinitionManager* manager, JsonValue* src, Def* parent)
			: ValueDef(manager, src, parent) {
			if (propertyIsUndefined(src, "size")) (*src)["size"].SetInt(0);
			if (!propertyIsPositiveIntOrZero(src, "size"))
				throw DefSourceError("Def source has invalid size: ", src);
		}

		size_t getSize() {
			return (*src)["size"].GetInt();
		}

		DataContainer* getData(ValueElement* element) {
			return new BytesData(element->getDataPtr(), element->getSize());
		}

		string getValue(ValueElement* element) {
			return getData(element)->getValue();
		}

		void setValue(ValueElement* element, string value) {
			// TODO
		}
	};

	string BytesDef::defType = "bytes";
	registerDef<BytesDef>();
}