#include "MaybeSubrecordDef.h"
#include "../elements/ValueElement.h"
#include "../data/DataContainer.h"

namespace esper {
	class ValueDef : public MaybeSubrecordDef {
	public:
		ValueDef(DefinitionManager* manager, JsonValue* src, Def* parent)
			: MaybeSubrecordDef(manager, src, parent) {}

		uint8_t* toBytes(uint8_t* data) {
			throw error("unimplemented");
		}

		MainRecord* getReferencedRecord(Element* element) {
			throw error(element->getName() + " does not reference records.");
		}

		ValueElement* build(Container* container, Subrecord* subrecord) {
			return new ValueElement(container, this, subrecord);
		}

		virtual DataContainer* getData(ValueElement* element) = 0;
	};
}