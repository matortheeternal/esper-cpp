#pragma once
#include <string>
#include <vector>

namespace esper {
	namespace PathResolution {
		using namespace std;

		class MatchData;
		class Element;

		typedef MatchData* (*MatchFunction)(Element* element, const string& pathPart);
		typedef Element* (*ResolveFunction)(MatchData* match);

		class ResolutionStrategy {
		public:
			ResolutionStrategy(
				int priority,
				MatchFunction matchFn,
				ResolveFunction resolveFn
			);

			int priority;
			MatchFunction match;
			ResolveFunction resolve;
		};

		using StrategyList = vector<ResolutionStrategy*>;
		StrategyList resolutionStrategies = StrategyList();
	}
}