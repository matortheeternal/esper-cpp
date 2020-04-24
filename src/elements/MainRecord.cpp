#include "MainRecord.h"
#include "../helpers/errors.h"
#include "../defs/MainRecordDef.h"
#include "../parsing/Signature.h"
#include "PluginFile.h"

namespace esper {
	MainRecord* MainRecord::load(Container* container, Signature* expectedSig = nullptr) {
		MainRecord* record = new MainRecord(container);
		record->loadHeader();
		if (expectedSig != nullptr && record->header->signature != *expectedSig)
			throw UnexpectedSignatureError(&record->header->signature, expectedSig);
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
			Def* memberDef = mrDef->getMemberDef(subrecord->signature);
			if (memberDef == nullptr) return; // TODO
			Element* element = memberDef->build(this);
			def->subrecordFound(element, subrecord);
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