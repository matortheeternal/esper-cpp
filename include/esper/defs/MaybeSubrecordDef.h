#ifndef ESPER_MAYBESUBRECORDDEF_H
#define ESPER_MAYBESUBRECORDDEF_H

#include "Def.h"
#include "../parsing/Signature.h"

namespace esper {
	class MaybeSubrecordDef : public Def {
	public:
		MaybeSubrecordDef(DefinitionManager* manager, JsonValue* src, Def* parent)
			: Def(manager, src, parent) {
			signature = Signature::fromJson(src);
		}

		bool isSubrecord() {
			return signature != nullptr;
		}

		bool hasSignature(Signature* signature) {
			return isSubrecord() && this->signature == signature;
		}

		string getName() {
			string name = (*src)["name"].GetString();
			return isSubrecord()
				? string(signature->data) + " - " + name
				: name;
		}

		Signature* signature;
	};
}

#endif