#pragma once
#include <cstdio>
#include <list>
#include <functional>
#include "stringbuffer.h"
#include "writer.h"
#include "filereadstream.h"
#include "document.h"
#include "errors.h"

namespace esper {
	using JsonValue = rapidjson::Value;
	using JsonDocument = rapidjson::Document;
	using JsonIterator = rapidjson::Value::ConstMemberIterator;
	using JsonEntryCallback = std::function<bool(const JsonValue&, const JsonValue&)>;

	using namespace std;

	JsonDocument* readJsonFile(string filePath) {
		FILE* fp = fopen(filePath.c_str(), "rb");
		char* readBuffer = new char[65536];
		rapidjson::FileReadStream fileStream(fp, readBuffer, 65536);
		static JsonDocument doc;
		if (doc.ParseStream(fileStream).HasParseError()) {
			fclose(fp);
			throw new error("Error parsing JSON " + filePath);
		}
		fclose(fp);
		return &doc;
	};

	JsonValue* objectAssign(JsonValue* target, const vector<JsonValue*>& sources, JsonDocument::AllocatorType& allocator) {
		for (size_t i = 0; i < sources.size(); i++) {
			JsonValue* source = sources[i];
			for (auto it = source->MemberBegin(); it != source->MemberEnd(); it++) {
				JsonValue name;
				name.CopyFrom(it->name, allocator);
				JsonValue value;
				value.CopyFrom(it->value, allocator);
				target->AddMember(name, value, allocator);
			}
		}
		return target;
	}

	string stringify(JsonValue& data) {
		rapidjson::StringBuffer sb;
		rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
		data.Accept(writer);
		return sb.GetString();
	}

	bool propertyIsUndefined(JsonValue& src, string key) {
		return !src.HasMember(key.c_str()) || src[key].IsNull();
	}

	bool propertyIsPositiveIntOrZero(JsonValue* value, string key) {
		return (*value)[key].IsInt() && (*value)[key].GetInt() >= 0;
	}

	JsonIterator* findEntry(JsonValue& value, JsonEntryCallback&& callback) {
		for (JsonIterator entry = value.MemberBegin(); entry != value.MemberEnd(); entry++)
			if (invoke(callback, entry->name, entry->value)) return &entry;
		return nullptr;
	}

	class DefSourceError : public error {
	public:
		DefSourceError(string msg, JsonValue& src)
			: error(msg + stringify(src)) {}
	};
}