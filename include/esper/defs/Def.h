#ifndef ESPER_DEF_H_
#define ESPER_DEF_H_

#include "../setup/DefinitionManager.h"
#include "../parsing/Signature.h"
#include "../parsing/Subrecord.h"

namespace esper {
	class Def {
	public:
		static string defType;

		Def(DefinitionManager* manager, JsonValue* src, void* parent) {
			this->manager = manager;
			this->src = src;
			this->parent = (Def*)parent;
		}

		virtual bool hasSignature(const Signature& signature) {
			return false;
		}

		virtual bool hasPrimarySignature(const Signature& signature) {
			return false;
		}

		virtual void* build(Container* container, Subrecord* subrecord) {
			throw error("unimplemented");
		}

		virtual string getName() {
			return (*src)["name"].GetString();
		}

		size_t getSize() {
			if (src->HasMember("size")) return (*src)["size"].GetUint();
			return 0;
		}

		DefinitionManager* manager;
		JsonValue* src;
		Def* parent;
		int sortOrder = 0;
	};
}

#endif