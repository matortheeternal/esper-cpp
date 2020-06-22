#pragma once
namespace esper {
	struct SessionOptions {
		bool keepMasterElementsUpdated = false;
		bool allowLightPlugins = true;
		bool emulateGlobalLoadOrder = true;
	};
}