#include "ResolutionStrategy.h"

namespace esper::PathResolution {
	ResolutionStrategy::ResolutionStrategy(
		int priority,
		MatchFunction matchFn,
		ResolveFunction resolveFn
	) : priority(priority), match(move(matchFn)), resolve(move(resolveFn)) {
		strategies.push_back(this);
	};
}