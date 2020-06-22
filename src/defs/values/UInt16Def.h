#pragma once
#include "IntegerDef.h"

namespace esper {
	class UInt16Def : public IntegerDef<uint16_t> {
	public:
		string getDefType() {
			return "uint16";
		}

		DataContainer* loadData(uint8_t* dataPtr);
		void setValue(ValueElement* element, string value);
		string getValue(ValueElement* element);
	};
}