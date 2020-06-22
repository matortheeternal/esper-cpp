#pragma once
#include "MatchData.h"
#include "../elements/Container.h"

namespace esper {
	namespace PathResolution {
		using namespace std;

		class ContainerMatch : public MatchData {
		public:
			ContainerMatch(Container* container, string pathPart)
				: MatchData(pathPart), container(container) {};

			ContainerMatch(Container* container, smatch match)
				: MatchData(match), container(container) {};

			Container* container;
		};
	}
}