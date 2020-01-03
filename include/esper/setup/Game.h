#ifndef ESPER_GAME_H_
#define ESPER_GAME_H_

#include <cstdint>
#include <vector>

namespace esper {
	using namespace std;

	class Game {
	public:
		bool supportsLightPlugins() {
			for (auto i = 0; i < pluginExtensions.size(); i++)
				if (pluginExtensions[i] == ".esl") return true;
		}

		uint8_t id;
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