#ifndef ESPER_DEFINITION_MANAGER_H_
#define ESPER_DEFINITION_MANAGER_H_

#include <string>
#include <vector>
#include <unordered_map>
#include "Game.h"
#include "../helpers/errors.h"
#include "../helpers/json.h"

namespace esper {
	using namespace std;

	class DefinitionManager {
	public:
		typedef void* (*create_def_function)(
			DefinitionManager* manager,
			JsonValue* def,
			void* parent
		);

		using DefMap = unordered_map<string, void*>;
		using DefFunctionMap = unordered_map<string, create_def_function>;

		static DefFunctionMap allDefClasses;

		DefFunctionMap getDefClasses(Game& game) {
			// TODO
		}

		DefMap buildRecordDefs(DefinitionManager* manager) {
			DefFunctionMap defClasses = manager->defClasses;
			// TODO
		}

		DefinitionManager(Game& game) {
			this->defs = readJsonFile("./defs/" + game.abbreviation + ".json");
			this->defClasses = getDefClasses(game);
			this->recordDefs = buildRecordDefs(this);
		}

		~DefinitionManager() {
			delete defs;
			delete& defClasses;
			delete& recordDefs;
		}

		JsonValue* resolveDef(string id) {
			if (!defs->HasMember(id)) throw error("Failed to resolve def: " + id);
			return &(*defs)[id];
		}

		create_def_function resolveDefClass(string defType) {
			return defClasses[defType];
		}

		void* buildDef(JsonValue& src, void* parent) {
			if (!src.IsObject()) throw error("Definition source must be an object.");
			if (src.HasMember("id")) {
				string id = src["id"].GetString();
				src = *objectAssign(
					new JsonValue(),
					{ &src, resolveDef(id) },
					defs->GetAllocator()
				);
			}
			string type = src["type"].GetString();
			create_def_function createDef = resolveDefClass(type);
			return createDef(this, &src, parent);
		}

		vector<void*>* buildDefs(
			rapidjson::GenericValue<
				rapidjson::UTF8<char>, 
				rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>
			>& defs, void* parent) {
			if (!defs.IsArray()) throw error("defs must be an array.");
			int sortOrder = 0;
			vector<void*>* builtDefs = new vector<void*>(defs.Size());
			for (auto it = defs.Begin(); it != defs.End(); it++) {
				void* def = buildDef(*it, parent);
				//def->sortOrder = sortOrder;
				(*builtDefs)[sortOrder++] = def;
			}
			return builtDefs;
		}

		JsonDocument* defs;
		DefMap recordDefs;
		DefFunctionMap defClasses;
	};

	using DefFunctionMap = DefinitionManager::DefFunctionMap;
	using DefMap = DefinitionManager::DefMap;

	DefFunctionMap DefinitionManager::allDefClasses = DefFunctionMap();

	template<class T> void registerDef(string defType) {
		DefinitionManager::allDefClasses[defType] = [](
			DefinitionManager* manager,
			JsonValue* def,
			void* parent
		) {
			return (void*)(new T(manager, def, parent));
		};
	}
}

#endif