#include "ResolutionStrategy.h"
#include "../elements/Element.h"
#include "../elements/Container.h"

namespace esper {
	namespace PathResolution {
		ResolutionStrategy::ResolutionStrategy(
			int priority,
			MatchFunction matchFn,
			ResolveFunction resolveFn
		) : priority(priority), match(matchFn), resolve(resolveFn) {
			resolutionStrategies.push_back(this);
		};
	}
}