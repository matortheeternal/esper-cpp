#pragma once
#include <cstdint>
#include "../helpers/errors.h"

namespace esper {
	class PluginFile;

	class PluginSlot {
	public:
		PluginSlot(PluginFile* plugin);

		virtual uint32_t getOrdinal();

		PluginFile* plugin;
	};

	class FullPluginSlot : public PluginSlot {
	public:
		FullPluginSlot(PluginFile* plugin, uint8_t index);

		uint32_t getOrdinal();

		uint8_t index;
	};

	class LightPluginSlot : public PluginSlot {
	public:
		static constexpr uint32_t BASE_ORDINAL = 0xFE000000;

		LightPluginSlot(PluginFile* plugin, uint16_t index);

		uint32_t getOrdinal();

		uint16_t index;
	};
}