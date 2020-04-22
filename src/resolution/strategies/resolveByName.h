#pragma once
#include "../../helpers/strings.h"
#include "../ResolutionStrategy.h"
#include "../ContainerMatch.h"
#include "../../elements/Element.h"
#include "../../elements/Container.h"

namespace esper {
	namespace PathResolution {
		ResolutionStrategy resolveByName = ResolutionStrategy(
			0,
			[](Element* element, const string& pathPart) -> MatchData* {
				Container* container = dynamic_cast<Container*>(element);
				if (container != nullptr)
					return new ContainerMatch(container, pathPart);
			},
			[](MatchData* match) -> Element* {
				ContainerMatch* c = (ContainerMatch*)match;
				vector<Element*> elements = c->container->assignedElements();
				for (Element* element : *elements) {
					if (strEquals(element->getName(), match->pathPart))
						return element;
				}
			}
		);
	}
}