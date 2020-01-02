#ifndef ESPER_DEF_H_
#define ESPER_DEF_H_

#include "../helpers/helpers.h"

namespace esper {
	class Def {
	public:
		static string defType;

		Def(DefinitionManager* manager, JsonValue* src, Def* parent) {
			this->manager = manager;
			this->src = src;
			this->parent = parent;
		}

		virtual bool hasSignature(Signature* signature) {
			return false;
		}

		virtual bool hasPrimarySignature(Signature* signature) {
			return false;
		}

		virtual void load(Element* container) {
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