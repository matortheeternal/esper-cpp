#pragma once
#include "MatchData.h"
#include "../elements/Element.h"

namespace esper {
	namespace PathResolution {
		using namespace std;

		class Element;

		class ElementMatch : public MatchData {
		public:
			ElementMatch(Element* element, string pathPart)
				: MatchData(pathPart), element(element) {};

			ElementMatch(Element* element, smatch match)
				: MatchData(match), element(element) {};

			Element* element;
		};
	}
}