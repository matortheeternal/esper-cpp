#include "PluginManager.h"

namespace esper {
	PluginManager::PluginManager(Game& game, Session* session)
		: usingLightPlugins(
			session->options->allowLightPlugins && 
			game.supportsLightPlugins()
		),
		maxLightPluginIndex(usingLightPlugins ? 4095 : 0),
		maxFullPluginIndex(usingLightPlugins ? 253 : 254),
		session(session) {}

	bool PluginManager::shouldUseLightSlot(PluginFile* plugin) {
		return usingLightPlugins && plugin->isEsl();
	}

	uint16_t PluginManager::nextLightPluginIndex() {
		uint16_t index = lightPluginSlots->size();
		if (index > maxLightPluginIndex)
			throw error("Maximum light plugins exceeded.");
		return index;
	}

	uint8_t PluginManager::nextFullPluginIndex() {
		uint8_t index = fullPluginSlots->size();
		if (index > maxFullPluginIndex)
			throw error("Maximum full plugins exceeded.");
		return index;
	}

	void PluginManager::assignLoadOrder(PluginFile* plugin) {
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

	void PluginManager::addFile(PluginFile* plugin) {
		plugins->push_back(plugin);
		if (!session->options->emulateGlobalLoadOrder) return;
		assignLoadOrder(plugin);
	}

	PluginFile* PluginManager::createDummyPlugin(wstring filename) {
		PluginFile* dummyPlugin = new PluginFile(session, filename);
		addFile(dummyPlugin);
		return dummyPlugin;
	}

	PluginFile* PluginManager::getFileByName(wstring filename, bool createDummyIfMissing) {
		for (auto& plugin : *plugins)
			if (wstrEquals(filename, plugin->filename)) return plugin;
		if (!createDummyIfMissing) return nullptr;
		return createDummyPlugin(filename);
	}
}