#include <string>
#include <vector>
#include <unordered_map>
#include "../helpers/json.h"
#include "../helpers/errors.h"

namespace esper {

	using namespace std;

	class DefinitionManager {
	public:
		DefinitionManager(string gameAbbreviation) {
			this->defs = readJsonFile("./defs/" + gameAbbreviation + ".json");
			this->defClasses = new unordered_map<string, create_def_function>();
			this->recordDefs = buildRecordDefs(this);
		}

		~DefinitionManager() {
			delete defs;
			delete recordDefs;
		}

		JsonValue* resolveDef(string id) {
			if (!defs->HasMember(id)) throw error("Failed to resolve def: " + id);
			return &defs[id];
		}

		create_def_function resolveDefClass(string defType) {
			return defClasses[defType];
		}

		Def* buildDef(JsonValue* src, Def* parent) {
			if (!src->IsObject()) throw error("Definition source must be an object.");
			if (src->HasMember("id")) {
				string id = (*src)["id"].GetString();
				src = objectAssign(new JsonValue(), { src, resolveDef(id) });
			}
			string type = (*src)["type"].GetString();
			create_def_function createDef = resolveDefClass(type);
			return static_cast<Def*>(createDef(this, src, parent));
		}

		vector<Def*>* buildDefs(JsonValue* defs, Def* parent) {
			if (!defs->IsArray()) throw error("defs must be an array.");
			int sortOrder = 0;
			vector<Def*>* builtDefs = new vector<Def*>(defs->Size());
			for (auto it = defs->Begin(); it != defs->End(); it++) {
				Def* def = buildDef(it, parent);
				def->sortOrder = sortOrder;
				(*builtDefs)[sortOrder++] = def;
			}
			return builtDefs;
		}

		JsonDocument* defs;
		vector<Def*>* recordDefs;
		unordered_map<string, create_def_function>* defClasses;
	};

	typedef void* (*create_def_function)(
		DefinitionManager* manager, 
		JsonValue* def, 
		Def* parent
	);

	template<class T> void registerDef() {
		create_def_function createDef = [](
			DefinitionManager* manager, 
			JsonValue* def, 
			Def* parent
		) {
			return new T(manager, def, parent);
		};
		defClasses[T::defType] = createDef;
	}
}