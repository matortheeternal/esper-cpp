#include "FlagsDef.h"

namespace esper {
	const regex unknownFlagExpr("^Unknown (\d+)$", regexOptions);

	FlagsDef<class T>::FlagsDef(DefinitionManager* manager, JsonValue& src, Def* parent)
		: FormatDef<T>(manager, src, parent) {
		if (propertyIsUndefined(src, "flags"))
			throw error("FlagsDef requires flags");
	};

	string FlagsDef<class T>::getFlagValue(uint8_t index) {
		JsonValue& flags = getFlags();
		string key = formatInt(index, 10);
		if (propertyIsUndefined(flags, key))
			return "Unknown " + index;
		return flags[key].GetString();
	}

	uint8_t FlagsDef<class T>::getFlagIndex(string flag) {
		JsonValue& flags = getFlags();
		uint8_t index;
		for (JsonIterator entry = flags.MemberBegin(); entry != flags.MemberEnd(); entry++) {
			if (entry->value.GetString() == flag) {
				if (tryStrToInt(entry->name.GetString(), index)) return index;
			}
		}
		smatch match;
		if (regex_search(flag, match, unknownFlagExpr))
			if (tryStrToInt(match[0], index)) return index;
		throw error("Invalid Flag Value: " + flag);
	}

	vector<string>* FlagsDef<class T>::dataToArray(Element* element, DataContainer* data) {
		vector<string>* a = new vector<string>();
		IntData<T>* intData = dynamic_cast<IntData<T>*>(data);
		uint8_t numBits = intData->getSize() * 8;
		for (uint8_t n = numBits - 1; n >= 0; n--)
			if (intData->getData() & (1 << n)) a->push_back(getFlagValue(n));
		return a;
	};

	string FlagsDef<class T>::dataToValue(Element* element, DataContainer* data) {
		
	};

	DataContainer* FlagsDef<class T>::valueToData(Element* element, string value) {
		
	};

	JsonValue& FlagsDef<class T>::getFlags() {
		return src["flags"];
	};
}