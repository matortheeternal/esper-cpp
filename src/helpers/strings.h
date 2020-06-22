#pragma once

#include <string>
#include <cstdint>
#include <regex>
#include <charconv>
#include <locale>
#include <codecvt>
#include <sstream>
#include "errors.h"

namespace esper {
	using namespace std;

	inline const auto regexOptions = regex_constants::syntax_option_type::optimize &
		regex_constants::syntax_option_type::ECMAScript;
	inline const regex bytesExpr("^([0-9A-Fa-f]{2} )*([0-9A-Fa-f]{2})$", regexOptions);
	inline const regex signatureExpr("^([^\\s]{4}) - ");

	inline const char digits[] = "01234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	template<class T>
	inline string formatInt(T value, uint8_t base = 10) {
		static_assert(is_integral_v<T>, "Integral required.");
		string result = "";
		for (size_t i = 0; i < sizeof(value); i++) {
			result = digits[value % base] + result;
			value /= base;
		}
		return result;
	}

	template<typename Type>
	inline string to_str(const Type& t) {
		ostringstream o;
		o << t;
		return o.str();
	}

	inline string formatBytes(uint8_t* data, size_t length) {
		string result = "";
		for (size_t i = 0; i < length; i++) {
			if (i != 0) result += " ";
			result += formatInt(data[i], 16);
		}
		return result;
	}

	inline string charToStr(char c) {
		const char* chars = new char[2]{ c, '\0' };
		return chars;
	}

	inline uint8_t parseHexDigit(char digit) {
		if (digit >= '0' && digit <= '9') return digit - '0';
		if (digit >= 'A' && digit <= 'F') return 10 + digit - 'A';
		if (digit >= 'a' && digit <= 'f') return 10 + digit - 'a';
		throw error(charToStr(digit) + " is not a valid hexadecimal character.");
	}

	inline uint8_t parseByte(const char* charPtr) {
		return 16 * parseHexDigit(charPtr[0]) + parseHexDigit(charPtr[1]);
	}

	inline void parseBytes(const string& value, uint8_t*& bytes, size_t& size) {
		if (!regex_match(value, bytesExpr))
			throw error("Invalid bytes value: " + value);
		size = (value.size() + 1) / 3;
		bytes = new uint8_t[size];
		const char* characters = value.c_str();
		for (size_t i = 0; i < size; i++)
			bytes[i] = parseByte(characters + 3 * i);
	}

	inline string extractSignature(const string& value) {
		if (value.size() == 4) return value;
		if (!regex_match(value, signatureExpr)) return "";
		return value.substr(0, 4);
	}
	
	template<class TValue>
	inline bool tryStrToFloat(
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
	inline bool tryStrToInt(
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

	inline float parseFloat(const string& value) {
		float fValue = 0;
		if (!tryStrToFloat(value, fValue))
			throw error("Input string '" + value + "' is not a float.");
		return fValue;
	}

	template<class T>
	inline T parseInt(const string& value) {
		T iValue = 0;
		if (!tryStrToInt<T>(value, iValue))
			throw error("Input string '" + value + "' is not an integer.");
		return iValue;
	}

	inline string wstringToString(wstring str) {
		return wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(str);
	}

	inline wstring stringToWString(string str) {
		return wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
	}

	inline string pad(string& s, uint8_t width, char c = ' ') {
		if (s.size() < width)
			s.insert(0, width - s.size(), c);
		return s;
	}

	template<class T>
	inline string intToHex(T n, uint8_t padding = 8) {
		string v = formatInt<T>(n, 16);
		return pad(v, padding, '0');
	}

	inline bool strEquals(const string& s1, const string& s2) {
		return _stricmp(s1.c_str(), s2.c_str()) == 0;
	}

	inline bool wstrEquals(const wstring& s1, const wstring& s2) {
		return _wcsicmp(s1.c_str(), s2.c_str()) == 0;
	}

	inline string join(vector<string>* v, string sep) {
		stringstream result;
		bool first = true;
		for (string& item : *v) {
			if (!first) result << sep;
			result << item;
			first = false;
		}
		return result.str();
	}

	inline vector<string>* split(string str, string delim) {
		vector<string>* v = new vector<string>();
		size_t start = 0;
		size_t end = str.find(delim);
		while (end != string::npos) {
			v->push_back(str.substr(start, end - start));
			start = end + delim.length();
			end = str.find(delim, start);
		}
		return v;
	}
}