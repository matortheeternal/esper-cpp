#include "MainRecord.h"
#include "../helpers/errors.h"
#include "../defs/MainRecordDef.h"
#include "PluginFile.h"
#include "../parsing/Signature.h"

namespace esper {
	MainRecord* MainRecord::build(Container* container, string expectedSig) {
		MainRecord* record = new MainRecord(container);
		record->loadHeader();
		if (expectedSig != "" && record->header->signature.data != expectedSig)
			throw UnexpectedSignatureError(record->header->signature.data, expectedSig);
		record->loadSubrecords();
		return record;
	}

	MainRecord* MainRecord::build(Container* container, vector<string>* expectedSigs) {
		MainRecord* record = new MainRecord(container);
		record->loadHeader();
		string recordSig = record->header->signature.data;
		bool foundSig = false;
		for (string& sig : *expectedSigs) {
			foundSig = recordSig == sig;
			if (foundSig) break;
		}
		if (!foundSig)
			throw UnexpectedSignatureError(recordSig, expectedSigs);
		record->loadSubrecords();
		return record;
	}

	vector<Subrecord*>* MainRecord::getUnknownSubrecords() {
		auto unknownSubrecords = new vector<Subrecord*>();
		MainRecordDef* mrDef = (MainRecordDef*)def;
		for (auto i = 0; i < subrecords->size(); i++) {
			Subrecord* subrecord = subrecords->at(i);
			if (!mrDef->hasMemberDef(subrecord->signature))
				unknownSubrecords->push_back(subrecord);
		}
		return unknownSubrecords;
	}

	void MainRecord::buildElements() {
		if (elements != nullptr) return;
		if (subrecords == nullptr) loadSubrecords();
		MainRecordDef* mrDef = (MainRecordDef*)def;
		initElements(mrDef->memberDefs->size());
		for (auto i = 0; i < subrecords->size(); i++) {
			Subrecord* subrecord = (*subrecords)[i];
			mrDef->subrecordFound(this, subrecord);
		}
	}

	void MainRecord::releaseElements() {
		if (elements == nullptr) return;
		delete elements;
		elements = nullptr;
	}

	bool MainRecord::ordered() {
		return true;
	}

	void MainRecord::loadHeader() {
		header = file->source->readRecordHeader();
		bodyOffset = file->source->getPos();
	}

	void MainRecord::loadSubrecords() {
		if (header == nullptr) throw error("Record header not loaded!");
		file->source->setPos(bodyOffset);
		subrecords = file->source->readSubrecords(header);
	}
}