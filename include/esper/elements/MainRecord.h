#include "Container.h"
#include "../helpers/errors.h"
#include "../parsing/Signature.h"
#include "../defs/MainRecordDef.h"
#include "../parsing/Subrecord.h"
#include "../parsing/RecordHeader.h"

class MainRecord : public Container {
public:
	MainRecord(Element* container, MainRecordDef* def = nullptr)
		: Container(container, def) {}

	static MainRecord* load(Element* container, Signature* expectedSig = nullptr) {
		MainRecord* record = new MainRecord(container);
		record->loadHeader();
		if (expectedSig != nullptr && record->header->signature != *expectedSig)
			throw UnexpectedSignatureError(record, expectedSig);
		record->loadSubrecords();
		return record;
	}

	vector<Subrecord*>* getUnknownSubrecords() {
		auto unknownSubrecords = new vector<Subrecord*>();
		MainRecordDef* mrDef = (MainRecordDef*) def;
		for (auto i = 0; i < subrecords->size(); i++) {
			Subrecord* subrecord = subrecords->at(i);
			if (!mrDef->hasMemberDef(subrecord->signature))
				unknownSubrecords->push_back(subrecord);
		}
		return unknownSubrecords;
	}

	void buildElements() {
		if (elements != nullptr) return;
		MainRecordDef* mrDef = (MainRecordDef*)def;
		initElements(mrDef->memberDefs->size());
		for (auto i = 0; i < subrecords->size(); i++) {
			Subrecord* subrecord = subrecords[i];
			Def* memberDef = mrDef->getMemberDef(subrecord->signature);
			if (memberDef != nullptr) memberDef->build(this, subrecord);
		}
	}

	void releaseElements() {
		if (elements == nullptr) return;
		delete elements;
		elements = nullptr;
	}

	bool sorted() {
		return true;
	}

	RecordHeader* header;
	uint32_t bodyOffset;
	vector<Subrecord*>* subrecords;

private:
	void loadHeader() {
		header = file->source->readRecordHeader();
		bodyOffset = file->source->getPos();
	}

	void loadSubrecords() {
		file->source->setPos(bodyOffset);
		subrecords = file->source->readSubrecords(header);
	}
};

class UnexpectedSignatureError : public error {
public:
	UnexpectedSignatureError(MainRecord* record, Signature* expectedSig)
		: error("Expected record signature " + expectedSig->data +
			", found: " + record->header->signature->data) {}
};