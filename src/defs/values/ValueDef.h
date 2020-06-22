#pragma once
#include "../MaybeSubrecordDef.h"
#include "../../parsing/Subrecord.h"
#include "../../setup/DefinitionManager.h"
#include "../../data/DataContainer.h"

namespace esper {
	class Element;
	class Container;
	class MainRecord;
	class ValueElement;

	class ValueDef : public MaybeSubrecordDef {
	public:
		ValueDef(DefinitionManager* manager, JsonValue& src, void* parent)
			: MaybeSubrecordDef(manager, src, parent) {}

		MainRecord* getReferencedRecord(Element* element);
		Element* build(Container* container);
		uint8_t* dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr);
		virtual DataContainer* loadData(uint8_t* dataPtr) = 0;
		virtual DataContainer* getData(ValueElement* element);
		void setData(ValueElement* element, DataContainer* data);
		string getValue(ValueElement* element);
		virtual void setValue(ValueElement* element, string value) = 0;
	};
}