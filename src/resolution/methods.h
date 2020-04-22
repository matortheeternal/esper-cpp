#pragma 
#include <string>
#include <vector>

namespace esper {
	namespace PathResolution {
		using namespace std;

		class Element;

		void splitPath(const string& path, string* pathPart, string* remainingPath);
		Element* resolveElement(Element* element, const string& pathPart);
		Element* getElement(Element* element, string path = "");
		vector<Element*> getElements(Element* element, string path = "");
	}
}