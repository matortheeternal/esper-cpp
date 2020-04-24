#include "EnumDef.h"

namespace esper {
	const regex unknownExpr("^<(?:Unknown )?(-?\d+)>$", regexOptions);

	EnumDef<class T>::EnumDef(DefinitionManager* manager, JsonValue& src, Def* parent)
		: FormatDef<T>(manager, src, parent) {
		if (propertyIsUndefined(src, "options"))
			throw error("EnumDef requires options");
	};

	string EnumDef<class T>::dataToValue(Element* element, DataContainer* data) {
		string dataValue = data->toString();
		JsonValue& options = getOptions();
		if (!propertyIsUndefined(options, dataValue))
			return options[dataValue].GetString();
		if (!propertyIsUndefined(src, "unknownOption"))
			return options["unknownOption"].GetString();
		return "<Unknown " + dataValue + ">";
	};

	DataContainer* EnumDef<class T>::valueToData(Element* element, string value) {
		JsonValue& opts = getOptions();
		for (JsonIterator entry = opts.MemberBegin(); entry != opts.MemberEnd(); entry++) {
			if (entry->name.GetString() == value)
				return new UserIntData<T>(entry->value.GetString());
		}
		smatch match;
		if (regex_search(value, match, unknownExpr))
			return new UserIntData<T>(match[1]);
		throw error("Invalid Enum Value: " + value);
	};

	JsonValue& EnumDef<class T>::getOptions() {
		return src["options"];
	};
}