#include <regex>
#include "../../helpers/strings.h"
#include "../ResolutionStrategy.h"
#include "../ContainerMatch.h"

namespace esper::PathResolution {
	static ResolutionStrategy resolveBySignature = ResolutionStrategy(
		0,
		[](Element* element, const string& pathPart) -> MatchData* {
			const string& signature = extractSignature(pathPart);
			if (signature.size() == 0) return nullptr;
			Container* container = dynamic_cast<Container*>(element);
			if (container != nullptr)
				return new ContainerMatch(container, signature);
			return nullptr;
		},
		[](MatchData* match) -> Element* {
			ContainerMatch* c = (ContainerMatch*)match;
			vector<Element*>* elements = c->container->elements;
			for (Element* element : *elements) {
				if (strEquals(element->getSignature(), match->pathPart))
					return element;
			}
			return nullptr;
		}
	);
}