#pragma once
#include "Element.h"
#include "Container.h"
#include "MainRecord.h"
#include "../parsing/Subrecord.h"
#include "../data/DataContainer.h"
#include "../flags/ElementState.h"

namespace esper {
class ValueElement : public Element {
public:
	ValueElement(Container* container, Def* def)
		: Element(container, def) {}

	DataContainer* getData();
	void setData(DataContainer* data);

	string getValue();
	void setValue(string value);
	MainRecord* getReferencedRecord();

	DataContainer* data = nullptr;
};
}