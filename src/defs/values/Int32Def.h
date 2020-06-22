#pragma once
#include "IntegerDef.h"

namespace esper {
	class Int32Def : public IntegerDef<uint8_t> {
	public:
		string getDefType() {
			return "uint32";
		}

		DataContainer* loadData(uint8_t* dataPtr);
		void setValue(ValueElement* element, string value);
		string getValue(ValueElement* element);
	};
}