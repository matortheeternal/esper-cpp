#pragma once

#include "Game.h"
#include "DefinitionManager.h"
#include "SessionOptions.h"
#include "PluginManager.h"

namespace esper {
	class Session {
	public:
		Session(Game& game, SessionOptions* options)
			: game(game), options(options) {
			this->definitionManager = new DefinitionManager(game);
			this->pluginManager = new PluginManager(game, this);
		}

		~Session() {
			free(options);
			free(definitionManager);
			free(pluginManager);
		}

		Game game;
		wstring dataPath;
		SessionOptions* options;
		DefinitionManager* definitionManager;
		PluginManager* pluginManager;
	};
}