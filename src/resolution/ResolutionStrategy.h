#pragma once
#include <string>
#include <vector>
#include <functional>
#include "MatchData.h"
#include "../elements/Element.h"

namespace esper::PathResolution {
	using namespace std;

	using MatchFunction = std::function<MatchData* (Element* element, const string& pathPart)>;
	using ResolveFunction = std::function<Element* (MatchData* match)>;

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
	inline StrategyList strategies = StrategyList();
}