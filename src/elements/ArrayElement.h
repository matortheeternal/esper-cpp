#pragma once

#include "Container.h"

namespace esper {
	class ArrayElement : public Container {
	public:
		ArrayElement(Container* container, Def* def)
			: Container(container, def) {}

		bool sorted() {
			// TODO
			return false;
		}
	};
}