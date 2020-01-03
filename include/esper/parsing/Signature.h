#ifndef ESPER_SIGNATURE_H_
#define ESPER_SIGNATURE_H_

#include "../helpers/errors.h"
#include "../helpers/json.h"

namespace esper {
	class Signature {
	public:
		Signature(const char* input) {
			memcpy(&data, input, 4);
		}

		static Signature* fromJson(JsonValue* src) {
			if (!src->HasMember("signature")) return nullptr;
			return new Signature((*src)["signature"].GetString());
		}

		bool operator==(Signature* other) const {
			return memcmp(data, other->data, 4) == 0;
		}

		bool operator!=(Signature* other) const {
			return !(this == other);
		}

		char data[4];
	};

	class UnexpectedSignatureError : public error {
	public:
		UnexpectedSignatureError(Signature* found, Signature* expected)
			: error(
				"Expected record signature " + string(expected->data) +
				", found: " + string(found->data)
			) {}
	};
}

#endif