#ifndef ESPER_PLUGIN_MANAGER_H_
#define ESPER_PLUGIN_MANAGER_H_

#include "Game.h"
#include <vector>
#include "LoadOrderSlot.h"

namespace esper {
	class PluginManager {
	public:
		PluginManager(Game& game, const SessionOptions* options)
			: usingLightPlugins(options->allowLightPlugins&& game.supportsLightPlugins()),
			maxLightPluginIndex(usingLightPlugins ? 4095 : 0),
			maxFullPluginIndex(usingLightPlugins ? 253 : 254),
			options(options) {}

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
			if (!options->emulateGlobalLoadOrder) return;
			assignLoadOrder(plugin);
		}

		const bool usingLightPlugins;
		const uint16_t maxLightPluginIndex;
		const uint8_t maxFullPluginIndex;
		const SessionOptions* options;

		vector<PluginFile*>* plugins = new vector<PluginFile*>();
		vector<FullPluginSlot*>* fullPluginSlots = new vector<FullPluginSlot*>();
		vector<LightPluginSlot*>* lightPluginSlots = new vector<LightPluginSlot*>();
	};
}

#endif