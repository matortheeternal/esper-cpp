#pragma once
#include "IntegerDef.h"

namespace esper {
	class UInt8Def : public IntegerDef<uint8_t> {
	public:
		string getDefType() {
			return "uint8";
		}

		DataContainer* loadData(uint8_t* dataPtr);
		void setValue(ValueElement* element, string value);
		string getValue(ValueElement* element);
	};
}