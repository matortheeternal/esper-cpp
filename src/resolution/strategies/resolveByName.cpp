#include "../../helpers/strings.h"
#include "../ResolutionStrategy.h"
#include "../ContainerMatch.h"

namespace esper::PathResolution {
	static ResolutionStrategy resolveByName = ResolutionStrategy(
		0,
		[](Element* element, const string& pathPart) -> MatchData* {
			Container* container = dynamic_cast<Container*>(element);
			if (container != nullptr)
				return new ContainerMatch(container, pathPart);
			return nullptr;
		},
		[](MatchData* match) -> Element* {
			ContainerMatch* c = (ContainerMatch*)match;
			vector<Element*>* elements = c->container->elements;
			for (Element* element : *elements) {
				if (strEquals(element->getName(), match->pathPart))
					return element;
			}
			return nullptr;
		}
	);
}