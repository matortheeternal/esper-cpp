#ifndef ESPER_GAME_H_
#define ESPER_GAME_H_

#include <cstdint>
#include <vector>

namespace esper {
	using namespace std;

	class Game {
	public:
		enum GameId {
			TES4 = 1,
			FO3 = 2,
			FNV = 3,
			TES5 = 4,
		    F76 = 5,
			FO4 = 6,
			SSE = 7
		};

		bool supportsLightPlugins() {
			for (auto i = 0; i < pluginExtensions.size(); i++)
				if (pluginExtensions[i] == ".esl") return true;
		}

		GameId id;
		string name;
		string fullName;
		string abbreviation;
		string registryName;
		string myGamesFolderName;
		string appDataFolderName;
		string exeName;
		string esmName;
		string iniName;
		string cccName;
		string pluginsTxtType;
		string archiveExtension;
		vector<string> pluginExtensions;
		vector<string> hardcodedPlugins;
		vector<uint32_t> steamAppIds;
	};
}

#endif