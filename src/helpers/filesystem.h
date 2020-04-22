#ifndef ESPER_FILESYSTEM_H_
#define ESPER_FILESYSTEM_H_

#include <string>
#include "errors.h"
#include "windows.h"

#ifdef _WIN32
char PATH_DELIMITER = '\\';
#else
char PATH_DELIMITER = '/';
#endif

namespace esper {
	using namespace std;

	wstring getFileName(const wstring& s) {
		size_t i = s.rfind(PATH_DELIMITER, s.length());
		if (i == string::npos) return L"";
		return s.substr(i + 1, s.length() - i);
	}

	void assertFileExists(const wstring& filePath) {
		DWORD attributes = GetFileAttributesW(filePath.c_str());
		if (attributes != INVALID_FILE_ATTRIBUTES) return;
		wstring message(filePath + L" does not exist, " + GetLastErrorAsStringW());
		throw error(reinterpret_cast<const char*>(message.c_str()));
	}
}

#endif