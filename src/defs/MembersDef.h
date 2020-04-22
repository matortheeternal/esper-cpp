#include "Def.h"
#include "../setup/DefinitionManager.h"
#include "../parsing/Subrecord.h"
#include "../parsing/Signature.h"

namespace esper {
	class MembersDef : public Def {
	public:
		MembersDef(DefinitionManager* manager, JsonValue& src, void* parent)
			: Def(manager, src, parent) {
			if (!src.HasMember("members"))
				throw DefSourceError("Expected def property 'members', found: ", src);
			memberDefs = manager->buildDefs(src["members"], this);
		}

		Def* getMemberDef(const Signature& signature) {
			for (auto i = 0; i < memberDefs->size(); i++) {
				Def* memberDef = (Def*)memberDefs->at(i);
				if (memberDef->hasSignature(signature))
					return memberDef;
			}
			return nullptr;
		}

		bool hasMemberDef(const Signature& signature) {
			return getMemberDef(signature) != nullptr;
		}

		bool hasSignature(const Signature& signature) {
			return hasMemberDef(signature);
		}

		vector<void*>* memberDefs;
	};
}