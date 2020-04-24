#pragma once

#include "Game.h"
#include <vector>
#include "PluginSlot.h"
#include "../helpers/strings.h"

namespace esper {
	class PluginManager {
	public:
		PluginManager(Game& game, Session* session)
			: usingLightPlugins(session->options->allowLightPlugins && game.supportsLightPlugins()),
			maxLightPluginIndex(usingLightPlugins ? 4095 : 0),
			maxFullPluginIndex(usingLightPlugins ? 253 : 254),
			session(session) {}

		bool shouldUseLightSlot(PluginFile* plugin) {
			return usingLightPlugins && plugin->isEsl();
		}

		uint16_t nextLightPluginIndex() {
			uint16_t index = lightPluginSlots->size();
			if (index > maxLightPluginIndex)
				throw error("Maximum light plugins exceeded.");
			return index;
		}

		uint8_t nextFullPluginIndex() {
			uint8_t index = fullPluginSlots->size();
			if (index > maxFullPluginIndex)
				throw error("Maximum full plugins exceeded.");
			return index;
		}

		void assignLoadOrder(PluginFile* plugin) {
			if (shouldUseLightSlot(plugin)) {
				lightPluginSlots->push_back(
					new LightPluginSlot(plugin, nextLightPluginIndex())
				);
			}
			else {
				fullPluginSlots->push_back(
					new FullPluginSlot(plugin, nextFullPluginIndex())
				);
			}
		}

		void addFile(PluginFile* plugin) {
			plugins->push_back(plugin);
			if (!session->options->emulateGlobalLoadOrder) return;
			assignLoadOrder(plugin);
		}

		PluginFile* createDummyPlugin(wstring filename) {
			PluginFile* dummyPlugin = new PluginFile(session, filename);
			addFile(dummyPlugin);
			return dummyPlugin;
		}

		PluginFile* getFileByName(wstring filename, bool createDummyIfMissing) {
			for (auto &plugin : *plugins) {
				if (wstrEquals(filename, plugin->filename)) return plugin;
			}
			if (!createDummyIfMissing) return nullptr;
			return createDummyPlugin(filename);
		}

		const bool usingLightPlugins;
		const uint16_t maxLightPluginIndex;
		const uint8_t maxFullPluginIndex;
		Session* session;

		vector<PluginFile*>* plugins = new vector<PluginFile*>();
		vector<FullPluginSlot*>* fullPluginSlots = new vector<FullPluginSlot*>();
		vector<LightPluginSlot*>* lightPluginSlots = new vector<LightPluginSlot*>();
	};
}