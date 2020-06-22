#pragma once
#include <unordered_map>

namespace esper {
	using namespace std;

	class MainRecord;

	template<class T>
	class RecordSet {
	public:
		using HashMap = unordered_map<T, MainRecord*>;

		RecordSet() : hashMap(HashMap()) {}

		MainRecord* find(const T key) {
			return hashMap.at(key);
		};

		HashMap hashMap;
	};
}