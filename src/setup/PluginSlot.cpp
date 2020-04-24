#include "./PluginSlot.h"

namespace esper {
	PluginSlot::PluginSlot(PluginFile* plugin) : plugin(plugin) {
		plugin->pluginSlot = this;
	}

	uint32_t PluginSlot::getOrdinal() {
		throw error("unimplemented");
	}

	FullPluginSlot::FullPluginSlot(PluginFile* plugin, uint8_t index)
		: PluginSlot(plugin), index(index) {}

	uint32_t FullPluginSlot::getOrdinal() {
		return index << 24;
	}

	LightPluginSlot::LightPluginSlot(PluginFile* plugin, uint16_t index)
		: PluginSlot(plugin), index(index) {}

	uint32_t LightPluginSlot::getOrdinal() {
		return BASE_ORDINAL | (index << 12);
	}
}