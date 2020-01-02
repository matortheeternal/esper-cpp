#ifndef ESPER_SIGNATURE_H_
#define ESPER_SIGNATURE_H_

namespace esper {
	class Signature {
	public:
		static size_t size;

		Signature(const char* input) {
			memcpy(&data, input, size);
		}

		static Signature* fromJson(JsonValue* src) {
			if (!src->HasMember("signature")) return nullptr;
			return new Signature((*src)["signature"].GetString());
		}

		bool operator==(Signature* other) const {
			return memcmp(data, other->data, size) == 0;
		}

		bool operator!=(Signature* other) const {
			return !(this == other);
		}

		char data[4];
	};

	size_t Signature::size = 4;
}

#endif