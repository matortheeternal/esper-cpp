#pragma once
#include <string>
#include <regex>

namespace esper {
	namespace PathResolution {
		using namespace std;

		class MatchData {
		public:
			MatchData(string pathPart) : pathPart(pathPart) {};
			MatchData(smatch match) : match(match) {};

			string pathPart;
			smatch match;
		};
	}
}