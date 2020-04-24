#ifndef ESPER_STRINGS_H_
#define ESPER_STRINGS_H_

#include <string>
#include <cstdint>
#include <regex>
#include <charconv>
#include <locale>
#include <codecvt>
#include "errors.h"

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
		size = (value.size() + 1) / 3;
		bytes = new uint8_t[size];
		const char* characters = value.c_str();
		for (size_t i = 0; i < size; i++)
			bytes[i] = parseByte(characters + 3 * i);
	}
	
	template<class TValue>
	bool tryStrToFloat(
		const string& stringValue, 
		TValue& value, 
		chars_format fmt = chars_format::general
	) {
		static_assert(is_floating_point_v<TValue>);
		return from_chars(
			stringValue.c_str(), 
			stringValue.c_str() + stringValue.size(),
			value, 
			fmt
		).ec == errc();
	}

	template<class TValue>
	bool tryStrToInt(
		const string& stringValue,
		TValue& value,
		chars_format fmt = chars_format::general
	) {
		static_assert(is_integral_v<TValue>);
		return from_chars(
			stringValue.c_str(),
			stringValue.c_str() + stringValue.size(),
			value,
			10
		).ec == errc();
	}

	float parseFloat(const string& value) {
		float fValue = 0;
		if (!tryStrToFloat(value, fValue))
			throw error("Input string '" + value + "' is not a float.");
		return fValue;
	}

	template<class T>
	T parseInt(const string& value) {
		T iValue = 0;
		if (!tryStrToInt<T>(value, iValue))
			throw error("Input string '" + value + "' is not an integer.");
		return iValue;
	}

	string wstringToString(wstring str) {
		return wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(str);
	}

	wstring stringToWString(string str) {
		return wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
	}

	string pad(string& s, uint8_t width, char c = ' ') {
		if (s.size() < width)
			s.insert(0, width - s.size(), c);
		return s;
	}

	template<class T>
	string intToHex(T n, uint8_t padding = 8) {
		string v = formatInt<T>(n, 16);
		return pad(v, padding, '0');
	}

	bool strEquals(const string& s1, const string& s2) {
		return _stricmp(s1.c_str(), s2.c_str()) == 0;
	}

	bool wstrEquals(const wstring& s1, const wstring& s2) {
		return _wcsicmp(s1.c_str(), s2.c_str()) == 0;
	}
}

#endif