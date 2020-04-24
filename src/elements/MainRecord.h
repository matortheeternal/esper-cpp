#pragma once
#include "Container.h"
#include "../parsing/Subrecord.h"
#include "../parsing/RecordHeader.h"

namespace esper {
	class MainRecord : public Container {
	public:
		MainRecord(Container* container, Def* def = nullptr)
			: Container(container, def) {}

		static MainRecord* load(Container* container, Signature* expectedSig = nullptr);
		vector<Subrecord*>* getUnknownSubrecords();
		void buildElements();
		void releaseElements();
		bool ordered();

		RecordHeader* header = nullptr;
		vector<Subrecord*>* subrecords = nullptr;
		uint32_t bodyOffset = 0;
	private:
		void loadHeader();
		void loadSubrecords();
	};
}