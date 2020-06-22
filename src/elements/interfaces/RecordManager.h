#pragma once
#include <vector>
#include <unordered_map>
#include "../helpers/RecordSet.h"
#include "../../data/FormIdData.h"

namespace esper {
	using namespace std;

	using PluginRecordSetMap = unordered_map<PluginFile*, RecordSet<uint32_t>*>;

	class PluginFile;
	class Element;

	class RecordManager {
	public:
		RecordManager() {
			localRecordsByFormId = new RecordSet<uint32_t>();
			remoteRecordsByFormId = new PluginRecordSetMap();
		}

		void addRemoteRecordSource(PluginFile* plugin) {
			remoteRecordsByFormId->emplace(
				plugin,
				new RecordSet<uint32_t>()
			);
		};

		MainRecord* getRecordByFormId(uint32_t formId);
		MainRecord* getRecordByLocalFormId(uint32_t localFormId);

		~RecordManager() {
			free(localRecordsByFormId);
			free(remoteRecordsByFormId);
		}

		RecordSet<uint32_t>* localRecordsByFormId;
		PluginRecordSetMap* remoteRecordsByFormId;
	};
}