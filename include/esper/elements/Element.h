#ifndef ESPER_ELEMENT_H_
#define ESPER_ELEMENT_H_

#include <string>

namespace esper {
	class Element {
	public:
		Element(Container* container, Def* def) {
			this->def = def;
			this->container = container;
			if (container == nullptr) return;
			this->file = container->file;
			container->elementAdded(this);
		}

		virtual string getSignature() {
			if (dynamic_cast<MaybeSubrecordDef*>(def))
				return ((MaybeSubrecordDef*)def)->signature;
		}

		virtual string getName() {
			return def->getName();
		}

		virtual string getPathName() {
			return getName();
		}

		virtual string getPath() {
			if (container == nullptr) return getPathName();
			return container->getPath() + "\\" + getPathName();
		}

		virtual size_t getSize() {
			return def->getSize();
		}

		virtual void getMasterReferences() {}

		// TODO: element resolution

		Def* def;
		Container* container;
		PluginFile* file = nullptr;
	};
}

#endif