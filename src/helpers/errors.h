#pragma once
#include "windows.h"
#include <stdexcept>
#include <string>

namespace esper {
	using namespace std;
	using error = runtime_error;

	inline wstring GetWindowsErrorW() {
		DWORD errorMessageID = ::GetLastError();
		if (errorMessageID == 0)
			return L"Unknown Error";

		LPWSTR messageBuffer = nullptr;
		size_t size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&messageBuffer, 0, NULL);

		wstring message(messageBuffer, size);
		LocalFree(messageBuffer);

		return message;
	}

	inline string GetWindowsError() {
		DWORD errorMessageID = ::GetLastError();
		if (errorMessageID == 0)
			return "Unknown Error";

		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		string message(messageBuffer, size);
		LocalFree(messageBuffer);

		return message;
	}
}