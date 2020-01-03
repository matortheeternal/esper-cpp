#ifndef ESPER_SESSION_OPTIONS_H_
#define ESPER_SESSION_OPTIONS_H_

namespace esper {
	struct SessionOptions {
		bool keepMasterElementsUpdated = false;
		bool allowLightPlugins = true;
		bool emulateGlobalLoadOrder = true;
	};
}

#endif