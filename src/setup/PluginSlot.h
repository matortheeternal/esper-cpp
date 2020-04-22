#ifndef ESPER_PLUGIN_SLOT_H_
#define ESPER_PLUGIN_SLOT_H_

#include <cstdint>
#include "../helpers/errors.h"

namespace esper {
	class PluginSlot;

	class PluginFile {
	public:
		bool isEsl() {}

		PluginSlot* pluginSlot;
	};

	class PluginSlot {
	public:
		PluginSlot(PluginFile* plugin) : plugin(plugin) {
			plugin->pluginSlot = this;
		}

		PluginFile* plugin;
	};

	class FullPluginSlot : public PluginSlot {
	public:
		FullPluginSlot(PluginFile* plugin, uint8_t index) 
		: PluginSlot(plugin), index(index) {}

		uint32_t getOrdinal() {
			return index << 24;
		}

		uint8_t index;
	};

	

	class LightPluginSlot : public PluginSlot {
	public:
		static constexpr uint32_t BASE_ORDINAL = 0xFE000000;

		LightPluginSlot(PluginFile* plugin, uint16_t index) 
		: PluginSlot(plugin), index(index) {}

		uint32_t getOrdinal() {
			return BASE_ORDINAL | (index << 12);
		}

		uint16_t index;
	};
}

#endif