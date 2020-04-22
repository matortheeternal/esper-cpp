#pragma once
#include "Container.h"

namespace esper {
	class StructElement : public Container {
	public:
		StructElement(Container* container, Def* def)
		: Container(container, def) {}

		bool getSorted() {
			return true;
		}
	};
}