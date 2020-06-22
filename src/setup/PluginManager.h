#pragma once

#include "Game.h"
#include <vector>
#include "PluginSlot.h"
#include "../helpers/strings.h"

namespace esper {
	class Session;

	class PluginManager {
	public:
		PluginManager(Game& game, Session* session);

		~PluginManager() {
			free(plugins);
			free(fullPluginSlots);
			free(lightPluginSlots);
		}

		bool shouldUseLightSlot(PluginFile* plugin);
		uint16_t nextLightPluginIndex();
		uint8_t nextFullPluginIndex();
		void assignLoadOrder(PluginFile* plugin);
		void addFile(PluginFile* plugin);
		PluginFile* createDummyPlugin(wstring filename);
		PluginFile* getFileByName(wstring filename, bool createDummyIfMissing);
		vector<wstring>* getMasterFilenames(wstring filePath);

		const bool usingLightPlugins;
		const uint16_t maxLightPluginIndex;
		const uint8_t maxFullPluginIndex;
		Session* session;

		vector<PluginFile*>* plugins = new vector<PluginFile*>();
		vector<FullPluginSlot*>* fullPluginSlots = new vector<FullPluginSlot*>();
		vector<LightPluginSlot*>* lightPluginSlots = new vector<LightPluginSlot*>();
	};
}