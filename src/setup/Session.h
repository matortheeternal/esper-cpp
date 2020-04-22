#ifndef ESPER_SESSION_H_
#define ESPER_SESSION_H_

#include "Game.h"
#include "DefinitionManager.h"
#include "SessionOptions.h";
#include "PluginManager.h"

namespace esper {
	class Session {
	public:
		Session(Game& game, SessionOptions* options) {
			this->game = game;
			this->options = options;
			this->definitionManager = new DefinitionManager(game);
			this->pluginManager = new PluginManager(game, options);
		}

		Game game;
		wstring dataPath;
		SessionOptions* options;
		DefinitionManager* definitionManager;
		PluginManager* pluginManager;
	};
}

#endif