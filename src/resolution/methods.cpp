#include "methods.h"
#include "ResolutionStrategy.h"
#include "../elements/ValueElement.h"

namespace esper::PathResolution {
	void splitPath(const string& path, string* pathPart, string* remainingPath) {
		size_t separatorIndex = path.find('\\');
		if (separatorIndex == -1) separatorIndex = path.size();
		*pathPart = path.substr(0, separatorIndex);
		*remainingPath = path.substr(separatorIndex + 1, path.size());
	}

	Element* resolveElement(Element* element, const string& pathPart) {
		for (ResolutionStrategy* strategy : strategies) {
			MatchData* match = invoke(strategy->match, element, pathPart);
			if (match != nullptr) return invoke(strategy->resolve, match);
		}
	}

	Element* getElement(Element* element, string path) {
		string pathPart;
		while (path.size() > 0) {
			splitPath(path, &pathPart, &path);
			element = resolveElement(element, pathPart);
		};
		return element;
	}

	vector<Element*> getElements(Element* element, string path) {
		Element* target = getElement(element, path);
		Container* container = dynamic_cast<Container*>(target);
		if (container == nullptr)
			throw error("Element does not have children.");
		return *container->elements;
	}

	string getValue(Element* element, string path) {
		Element* target = getElement(element, path);
		ValueElement* valueElement = dynamic_cast<ValueElement*>(target);
		if (valueElement == nullptr)
			throw error("Element does not have a value.");
		return valueElement->data->toString();
	}
}