#pragma once

#include "Def.h"
#include "../parsing/Signature.h"

namespace esper {
	class MaybeSubrecordDef : public Def {
	public:
		MaybeSubrecordDef(DefinitionManager* manager, JsonValue& src, void* parent)
			: Def(manager, src, parent) {
			signature = Signature::fromJson(src);
		}

		void subrecordFound(Element* element, Subrecord* subrecord) {
			if (subrecord->signature != signature)
				throw new error("subrecord signature mismatch");
			dataFound(element, subrecord->getData(), subrecord->getEnd());
		}

		bool isSubrecord() {
			return signature != nullptr;
		}

		bool hasSignature(Signature* signature) {
			return isSubrecord() && this->signature == signature;
		}

		string getSignature() {
			if (!isSubrecord()) return "";
			return string(signature->data);
		}

		string getName() {
			string name = src["name"].GetString();
			return isSubrecord()
				? getSignature() + " - " + name
				: name;
		}

		Signature* signature;
	};
}