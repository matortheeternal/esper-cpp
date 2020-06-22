#include "PluginManager.h"
#include "Session.h"
#include "../elements/PluginFile.h"

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
		return new PluginFile(session, filename);
	}

	PluginFile* PluginManager::getFileByName(wstring filename, bool createDummyIfMissing) {
		for (auto& plugin : *plugins)
			if (wstrEquals(filename, plugin->filename)) return plugin;
		if (!createDummyIfMissing) return nullptr;
		return createDummyPlugin(filename);
	}

	vector<wstring>* PluginManager::getMasterFilenames(wstring filePath) {
		PluginFileOptions options = { true };
		PluginFile* plugin = new PluginFile(session, filePath, options);
		plugin->source = new PluginFileSource(filePath);
		plugin->loadFileHeader();
		vector<wstring>* masterFilenames = plugin->getMasterFilenames();
		delete plugin;
		return masterFilenames;
	}
}