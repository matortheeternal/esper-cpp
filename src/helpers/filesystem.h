#pragma once
#include <string>
#include "errors.h"
#include "windows.h"

namespace esper {
	using namespace std;

#ifdef _WIN32
	inline const char PATH_DELIMITER = '\\';
#else
	inline const char PATH_DELIMITER = '/';
#endif

	inline wstring getFileName(const wstring& s) {
		size_t i = s.rfind(PATH_DELIMITER, s.length());
		if (i == string::npos) return L"";
		return s.substr(i + 1, s.length() - i);
	}

	inline void assertFileExists(const wstring& filePath) {
		DWORD attributes = GetFileAttributesW(filePath.c_str());
		if (attributes != INVALID_FILE_ATTRIBUTES) return;
		wstring message(filePath + L" does not exist, " + GetWindowsErrorW());
		throw error(reinterpret_cast<const char*>(message.c_str()));
	}
}