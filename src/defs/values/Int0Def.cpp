#include "Int0Def.h"
#include "../../elements/ValueElement.h"
#include "../../data/Int0Data.h"

namespace esper {
	DataContainer* Int0Def::loadData(uint8_t* dataPtr) {
		return new Int0Data();
	}

	string Int0Def::defType = "int0";
}