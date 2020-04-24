#pragma once
#include <string>
#include "../flags/ElementState.h"

namespace esper {
	class Def;
	class Container;
	class PluginFile;

	class Element {
	public:
		Element() {}
		Element(Container* container, Def* def);
		virtual string getName();
		virtual string getPathName();
		virtual string getPath();
		virtual size_t getSize();
		virtual void getMasterReferences();

		Def* def = nullptr;
		Container* container = nullptr;
		PluginFile* file = nullptr;
		ElementState state = ElementState();
	};
}