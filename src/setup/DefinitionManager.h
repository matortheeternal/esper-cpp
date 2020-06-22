#pragma once

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include "Game.h"
#include "../helpers/errors.h"
#include "../helpers/json.h"

namespace esper {
	using namespace std;

	class DefinitionManager {
	public:
		using CreateDefFunction = std::function<void* (
			DefinitionManager* manager,
			JsonValue& def,
			void* parent
		)>;

		using DefMap = unordered_map<string, void*>;
		using DefFunctionMap = unordered_map<string, CreateDefFunction>;
		using GameDefsMap = unordered_map<Game*, DefFunctionMap*>;

		inline static DefFunctionMap generalDefClasses = DefFunctionMap();
		inline static GameDefsMap gameDefClasses = GameDefsMap();

		DefinitionManager(Game& game) {
			readDefs(game);
			initDefClasses(game);
			buildRecordDefs();
		}

		~DefinitionManager() {
			free(defs);
			free(defClasses);
			free(recordDefs);
		}

		void readDefs(Game& game) {
			defs = readJsonFile("./defs/" + game.abbreviation + ".json");
		}

		void initDefClasses(Game& game) {
			defClasses = new DefFunctionMap();
			defClasses->insert(
				generalDefClasses.begin(),
				generalDefClasses.end()
			);
			defClasses->insert(
				gameDefClasses[&game]->begin(),
				gameDefClasses[&game]->end()
			);
		}

		void buildRecordDefs() {
			recordDefs = new DefMap();
			forEachEntry(defs, [&](const JsonValue& name, const JsonValue& value) {
				recordDefs->at(name.GetString()) = buildDef(value, nullptr);
			});
		}

		JsonValue* resolveDef(string id) {
			if (!defs->HasMember(id)) throw error("Failed to resolve def: " + id);
			return &(*defs)[id];
		}

		CreateDefFunction resolveDefClass(string defType) {
			return defClasses->at(defType);
		}

		void* buildDef(const JsonValue& input, void* parent = nullptr) {
			JsonValue& src = const_cast<JsonValue&>(input);
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
			CreateDefFunction createDef = resolveDefClass(type);
			return invoke(createDef, this, src, parent);
		}

		vector<void*>* buildDefs(
			rapidjson::GenericValue<
				rapidjson::UTF8<char>, 
				rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>
			>& defs, void* parent) {
			if (!defs.IsArray()) throw error("defs must be an array.");
			int index = 0;
			vector<void*>* builtDefs = new vector<void*>(defs.Size());
			for (auto it = defs.Begin(); it != defs.End(); it++) {
				void* def = buildDef(*it, parent);
				//def->index = index;
				(*builtDefs)[index++] = def;
			}
			return builtDefs;
		}

		void* getFileHeaderDef() {
			return recordDefs->at("TES4");
		}

		JsonDocument* defs;
		DefMap* recordDefs;
		DefFunctionMap* defClasses;
	};

	template<class T> inline void registerDef(string defType) {
		DefinitionManager::generalDefClasses[defType] = [](
			DefinitionManager* manager,
			JsonValue& def,
			void* parent
		) -> void* {
			return (void*)(new T(manager, def, parent));
		};
	}

	template<class T> inline void registerDef(Game& game, string defType) {
		DefinitionManager::gameDefClasses[&game][defType] = [](
			DefinitionManager* manager,
			JsonValue& def,
			void* parent
		) -> void* {
			return (void*)(new T(manager, def, parent));
		};
	}
}