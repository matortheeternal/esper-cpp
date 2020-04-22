#pragma once
#include "../setup/DefinitionManager.h"
#include "../parsing/Signature.h"
#include "../parsing/Subrecord.h"

namespace esper {
	class Element;
	class Container;

	class Def {
	public:
		static string defType;

		Def(DefinitionManager* manager, JsonValue& src, void* parent)
		: manager(manager), src(src), parent((Def*)parent) {}

		virtual bool hasSignature(const Signature& signature) {
			return false;
		}

		virtual bool hasPrimarySignature(const Signature& signature) {
			return false;
		}

		virtual Element* build(Container* container) {
			throw error("unimplemented");
		}

		virtual void subrecordFound(Element* element, Subrecord* subrecord) {
			dataFound(element, subrecord->getData(), subrecord->getEnd());
		}

		virtual uint8_t* dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr) {
			throw error("unimplemented");
		}

		virtual string getName();
		size_t getSize();

		DefinitionManager* manager;
		JsonValue& src;
		Def* parent;
		int sortOrder = 0;
	};
}