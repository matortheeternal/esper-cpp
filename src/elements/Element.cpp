#include "../defs/Def.h"
#include "Element.h"
#include "Container.h"
#include "PluginFile.h"
#include "../defs/MaybeSubrecordDef.h"

namespace esper {
	Element::Element(Container* container, Def* def) {
		this->def = def;
		this->container = container;
		if (container == nullptr) return;
		this->file = container->file;
		container->elementAdded(this);
	}

	string Element::getName() {
		return def->getName();
	}

	string Element::getSignature() {
		MaybeSubrecordDef* d = dynamic_cast<MaybeSubrecordDef*>(this->def);
		if (d == nullptr || !d->isSubrecord()) return "";
		return string(d->signature->data);
	}

	string Element::getPathName() {
		return getName();
	}

	string Element::getPath() {
		if (container == nullptr) return getPathName();
		return container->getPath() + "\\" + getPathName();
	}

	size_t Element::getSize() {
		return def->getSize();
	}

	void Element::getMasterReferences() {}
}