#include "DefinitionManager.h"
#include "SessionOptions.h";
#include "PluginManager.h"

namespace esper {
	class Session {
	public:
		Session(int gameId, SessionOptions* options) {
			this->gameId = gameId;
			this->options = options;
			this->definitionManager = new DefinitionManager(gameId);
			this->pluginManager = new PluginManager(gameId);
		}

		wstring dataPath;
		SessionOptions* options;
		DefinitionManager* definitionManager;
		PluginManager* pluginManager;
	};
}