#pragma once
#include "FormatDef.h"

namespace esper {
	const regex unknownFlagExpr("^Unknown (\d+)$", regexOptions);

	template<class T>
	class FlagsDef : public FormatDef<T> {
	public:
		FlagsDef(DefinitionManager* manager, JsonValue& src, Def* parent)
			: FormatDef<T>(manager, src, parent) {
			if (propertyIsUndefined(src, "flags"))
				throw error("FlagsDef requires flags");
		};

		string getFlagValue(uint8_t index) {
			JsonValue& flags = src["flags"];
			string key = formatInt(index, 10);
			if (propertyIsUndefined(flags, key))
				return "Unknown " + index;
			return flags[key].GetString();
		};

		uint8_t getFlagIndex(string flag) {
			JsonValue& flags = src["flags"];
			uint8_t index;
			auto* entry = findEntry(flags, [&](auto& name, auto& value) {
				return value.GetString() == flag;
			});
			if (entry != nullptr) {
				string indexValue = (*entry)->name.GetString();
				if (tryStrToInt(indexValue, index)) return index;
			}
			smatch match;
			if (regex_search(flag, match, unknownFlagExpr))
				if (tryStrToInt(match[0], index)) return index;
			throw error("Invalid Flag Value: " + flag);
		};

		vector<string>* dataToArray(Element* element, DataContainer* data) {
			vector<string>* a = new vector<string>();
			IntData<T>* intData = dynamic_cast<IntData<T>*>(data);
			uint8_t numBits = intData->getSize() * 8;
			for (uint8_t n = numBits - 1; n >= 0; n--)
				if (intData->getData() & (1 << n)) a->push_back(getFlagValue(n));
			return a;
		};

		string dataToValue(Element* element, DataContainer* data) {
			return join(dataToArray(element, data), ", ");
		};

		DataContainer* valueToData(string value) {
			if (value == "") return 0;
			T data = 0;
			vector<string>* flags = split(value, ", ");
			for (string& flag : *flags)
				data += getFlagIndex(flag);
			return new UserIntData<T>(data);
		};

		JsonValue& getFlags() {
			return src["flags"];
		};
	};

	using UInt32FlagsDef = FlagsDef<uint32_t>;
	using UInt16FlagsDef = FlagsDef<uint16_t>;
	using UInt8FlagsDef = FlagsDef<uint8_t>;
	using Int32FlagsDef = FlagsDef<int32_t>;
	using Int16FlagsDef = FlagsDef<int16_t>;
	using Int8FlagsDef = FlagsDef<int8_t>;
}