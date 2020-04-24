#pragma once
#include "IntData.h"

namespace esper {
	class PluginFile;
	class MainRecord;

	class FormIdData : public IntData<uint32_t> {
	public: 
		FormIdData() {}

		FormIdData(PluginFile* file, uint8_t* dataPtr)
			: file(file), IntData<uint32_t>(dataPtr) {};

		uint8_t getLocalOrdinal() {
			return *dataPtr;
		}

		uint32_t getLocalFormId() {
			return getData() & 0x00FFFFFF;
		}

		bool isNull() {
			return getLocalFormId() == 0;
		}

		uint32_t toGlobalFormId();
		string toString();
		MainRecord* resolveRecord();

		PluginFile* file;
	};
}