#include "fileapi.h"
#include "memoryapi.h"
#include <vector>
#include <cstdint>
#include <exception>
#include <string>
#include "../helpers/errors.h"

using namespace std;

class MemoryMap {
public:
	MemoryMap(wstring filePath) {
		fileHandle = CreateFileW(
			filePath.c_str(),
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_RANDOM_ACCESS,
			0
		);
		if (fileHandle == NULL) {
			string err = "Error creating file handle:\n" + GetLastErrorAsString();
			throw error(err.c_str());
		}

		mapHandle = CreateFileMapping(
			fileHandle,
			NULL,
			PAGE_READONLY,
			0,
			0,
			NULL
		);
		if (mapHandle == NULL) {
			string err = "Error creating map handle:\n" + GetLastErrorAsString();
			throw error(err.c_str());
		}

		viewPtr = MapViewOfFileEx(
			mapHandle,
			FILE_MAP_READ,
			0,
			0,
			0,
			NULL
		);
		if (viewPtr == NULL) {
			string err = "Error creating view pointer:\n" + GetLastErrorAsString();
			throw error(err.c_str());
		}

		fileSize = GetFileSize(fileHandle_, NULL);
		startPtr = static_cast<uint8_t*>(viewPtr);
		dataPtr = startPtr;
		endPtr = dataPtr + fileSize;
	}

	~MemoryMap() {
		if (viewPtr) UnmapViewOfFile(viewPtr);
		if (mapHandle) CloseHandle(mapHandle);
		if (fileHandle) CloseHandle(fileHandle);
	}

	uint32_t getSize() {
		return (uint32_t)fileSize;
	}

	uint32_t getPos() {
		return (uint32_t)dataPtr - startPtr;
	}

	void setPos(uint32_t newPos) {
		if (newPos > fileSize)
			throw error("Position out of bounds.");
		dataPtr = startPtr + newPos;
	}

	void* copy(uint32_t length) {
		if (dataPtr + length > endPtr)
			throw error("Read out of bounds.");
		void* result = malloc(length);
		memcpy(result, dataPtr, length);
		dataPtr += length;
		return result;
	}

	bool match(const uint8_t* bytes, size_t size) {
		if (dataPtr + size > endPtr)
			throw error("Read out of bounds.");
		return memcmp(dataPtr, bytes, size) == 0;
	}

private:
	DWORD fileSize = 0;
	HANDLE fileHandle = nullptr;
	HANDLE mapHandle = nullptr;
	LPVOID viewPtr = nullptr;
	uint8_t* startPtr = nullptr;
	uint8_t* dataPtr = nullptr;
	uint8_t* endPtr = nullptr;
};