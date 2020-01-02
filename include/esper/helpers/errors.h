#ifndef ESPER_ERRORS_H
#define ESPER_ERRORS_H

#include "windows.h"
#include <stdexcept>
#include "json.h"

namespace esper {
	using error = std::runtime_error;

	class DefSourceError : public error {
	public:
		DefSourceError(string msg, JsonValue* src)
			: error(msg + stringify(src)) {}
	};

	string GetLastErrorAsString() {
		DWORD errorMessageID = ::GetLastError();
		if (errorMessageID == 0)
			return string("Unknown Error");

		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		string message(messageBuffer, size);
		LocalFree(messageBuffer);

		return message;
	}
}

#endif