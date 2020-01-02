#ifndef ESPER_STRINGS_H_
#define ESPER_STRINGS_H_

#include <string>
#include <cstdint>
#include <regex>

namespace esper {
	using namespace std;

	const auto regexOptions = regex_constants::syntax_option_type::optimize &
		regex_constants::syntax_option_type::ECMAScript;
	const regex bytesExpr("^([0-9A-Fa-f]{2} )*([0-9A-Fa-f]{2})$", regexOptions);

	const char digits[] = "01234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	template<class T> static string formatInt(T value, uint8_t base = 10) {
		static_assert(is_integral_v<T>, "Integral required.");
		string result = "";
		for (size_t i = 0; i < sizeof(value); i++) {
			result = digits[value % base] + result;
			value /= base;
		}
		return result;
	}

	string formatBytes(uint8_t* data, size_t length) {
		string result = "";
		for (size_t i = 0; i < length; i++) {
			if (i != 0) result += " ";
			result += formatInt(data[i], 16);
		}
		return result;
	}

	string charToStr(char c) {
		const char* chars = new char[2]{ c, '\0' };
		return chars;
	}

	uint8_t parseHexDigit(char digit) {
		if (digit >= '0' && digit <= '9') return digit - '0';
		if (digit >= 'A' && digit <= 'F') return 10 + digit - 'A';
		if (digit >= 'a' && digit <= 'f') return 10 + digit - 'a';
		throw error(charToStr(digit) + " is not a valid hexadecimal character.");
	}

	uint8_t parseByte(const char* charPtr) {
		return 16 * parseHexDigit(charPtr[0]) + parseHexDigit(charPtr[1]);
	}

	void parseBytes(const string& value, uint8_t*& bytes, size_t& size) {
		if (!regex_match(value, bytesExpr))
			throw error("Invalid bytes value: " + value);
		size = (value.length + 1) / 3;
		bytes = new uint8_t[size];
		const char* characters = value.c_str();
		for (auto i = 0; i < size; i++)
			bytes[i] = parseByte(characters + 3 * i);
	}
}

#endif