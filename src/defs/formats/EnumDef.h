#pragma once
#include "FormatDef.h"

namespace esper {
	const regex unknownExpr("^<(?:Unknown )?(-?\d+)>$", regexOptions);

	template<class T>
	class EnumDef : public FormatDef<T> {
	public:
		EnumDef(DefinitionManager* manager, JsonValue& src, Def* parent)
			: FormatDef<T>(manager, src, parent) {
			if (propertyIsUndefined(src, "options"))
				throw error("EnumDef requires options");
		};

		string dataToValue(Element* element, DataContainer* data) {
			string dataValue = data->toString();
			JsonValue& options = getOptions();
			if (!propertyIsUndefined(options, dataValue))
				return options[dataValue].GetString();
			if (!propertyIsUndefined(src, "unknownOption"))
				return options["unknownOption"].GetString();
			return "<Unknown " + dataValue + ">";
		};

		DataContainer* valueToData(Element* element, string value) {
			JsonValue& opts = getOptions();
			auto* entry = findEntry(opts, [&](auto& name, auto& value) {
				return name.GetString() == value;
			});
			if (entry != nullptr) {
				string indexValue = (*entry)->value.GetString();
				return new UserIntData<T>(indexValue);
			}
			smatch match;
			if (regex_search(value, match, unknownExpr))
				return new UserIntData<T>(match[1]);
			throw error("Invalid Enum Value: " + value);
		};

		JsonValue& getOptions() {
			return src["options"];
		};
	};
}