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

		Def(DefinitionManager* manager, JsonValue& src, void* parent);
		virtual bool hasSignature(const Signature& signature);
		virtual bool hasPrimarySignature(const Signature& signature);
		virtual Element* build(Container* container);
		virtual void subrecordFound(Element* element, Subrecord* subrecord);
		virtual uint8_t* dataFound(Element* element, uint8_t* dataPtr, uint8_t* endPtr);
		virtual string getName();
		size_t getSize();

		DefinitionManager* manager;
		JsonValue& src;
		Def* parent;
		int sortOrder = 0;
	};
}