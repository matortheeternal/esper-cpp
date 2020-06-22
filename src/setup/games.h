#pragma once
#include "Game.h"
#include <unordered_map>

namespace esper {
	Game Oblivion = {
		/*id*/						Game::TES4,
		/*name*/					"Oblivion",
		/*fullName*/				"The Elder Scrolls IV: Oblivion",
		/*abbreviation*/			"TES4",
		/*registryName*/			"Oblivion",
		/*myGamesFolderName*/		"Oblivion",
		/*appDataFolderName*/		"Oblivion",
		/*exeName*/					"Oblivion.exe",
		/*esmName*/					"Oblivion.esm",
		/*iniName*/					"Oblivion.ini",
		/*cccName*/					NULL,
		/*pluginsTxtType*/			"plain",
		/*archiveExtension*/		".bsa",
		/*pluginExtensions*/		{".esp", ".esm"},
		/*hardcodedPlugins*/		{"Oblivion.esm"},
		/*steamAppIds*/				{22330,9008883}
	};

	Game Fallout3 = {
		/*id*/						Game::FO3,
		/*name*/					"Fallout 3",
		/*fullName*/				"Fallout 3",
		/*abbreviation*/			"FO3",
		/*registryName*/			"Fallout 3",
		/*myGamesFolderName*/		"Fallout 3",
		/*appDataFolderName*/		"Fallout 3",
		/*exeName*/					"Fallout3.exe",
		/*esmName*/					"Fallout3.esm",
		/*iniName*/					"Fallout.ini",
		/*cccName*/					NULL,
		/*pluginsTxtType*/			"plain",
		/*archiveExtension*/		".bsa",
		/*pluginExtensions*/		{".esp", ".esm"},
		/*hardcodedPlugins*/		{"Fallout3.esm"},
		/*steamAppIds*/				{22300,22370}
	};

	Game FalloutNV = {
		/*id*/						Game::FNV,
		/*name*/					"Fallout NV",
		/*fullName*/				"Fallout: New Vegas",
		/*abbreviation*/			"FNV",
		/*registryName*/			"Fallout New Vegas",
		/*myGamesFolderName*/		"FalloutNV",
		/*appDataFolderName*/		"FalloutNV",
		/*exeName*/					"FalloutNV.exe",
		/*esmName*/					"FalloutNV.esm",
		/*iniName*/					"Fallout.ini",
		/*cccName*/					NULL,
		/*pluginsTxtType*/			"plain",
		/*archiveExtension*/		".bsa",
		/*pluginExtensions*/		{".esp", ".esm"},
		/*hardcodedPlugins*/		{"FalloutNV.esm"},
		/*steamAppIds*/				{22380,2028016}
	};

	Game Skyrim = {
		/*id*/						Game::TES5,
		/*name*/					"Skyrim",
		/*fullName*/				"The Elder Scrolls V: Skyrim",
		/*abbreviation*/			"TES5",
		/*registryName*/			"Skyrim",
		/*myGamesFolderName*/		"Skyrim",
		/*appDataFolderName*/		"Skyrim",
		/*exeName*/					"TESV.exe",
		/*esmName*/					"Skyrim.esm",
		/*iniName*/					"Skyrim.ini",
		/*cccName*/					NULL,
		/*pluginsTxtType*/			"plain",
		/*archiveExtension*/		".bsa",
		/*pluginExtensions*/		{".esp", ".esm"},
		/*hardcodedPlugins*/		{"Skyrim.esm", "Update.esm"},
		/*steamAppIds*/				{72850}
	};

	Game Fallout4 = {
		/*id*/						Game::FO4,
		/*name*/					"Fallout 4",
		/*fullName*/				"Fallout 4",
		/*abbreviation*/			"FO4",
		/*registryName*/			"Fallout4",
		/*myGamesFolderName*/		"Fallout4",
		/*appDataFolderName*/		"Fallout4",
		/*exeName*/					"Fallout4.exe",
		/*esmName*/					"Fallout4.esm",
		/*iniName*/					"Fallout4.ini",
		/*cccName*/					"Fallout4.ccc",
		/*pluginsTxtType*/			"asterisk",
		/*archiveExtension*/		".ba2",
		/*pluginExtensions*/		{".esp", ".esm", ".esl"},
		/*hardcodedPlugins*/		{
										"Fallout4.esm", 
										"DLCRobot.esm",
										"DLCworkshop01.esm",
										"DLCCoast.esm",
										"DLCworkshop02.esm",
										"DLCworkshop03.esm",
										"DLCNukaWorld.esm",
										"DLCUltraHighResolution.esm"
									},
		/*steamAppIds*/				{377160}
	};

	Game SkyrimSE = {
		/*id*/						Game::SSE,
		/*name*/					"Skyrim SE",
		/*fullName*/				"Skyrim: Special Edition",
		/*abbreviation*/			"SSE",
		/*registryName*/			"Skyrim Special Edition",
		/*myGamesFolderName*/		"Skyrim Special Edition",
		/*appDataFolderName*/		"Skyrim Special Edition",
		/*exeName*/					"SkyrimSE.exe",
		/*esmName*/					"Skyrim.esm",
		/*iniName*/					"Skyrim.ini",
		/*cccName*/					"Skyrim.ccc",
		/*pluginsTxtType*/			"asterisk",
		/*archiveExtension*/		".bsa",
		/*pluginExtensions*/		{".esp", ".esm", ".esl"},
		/*hardcodedPlugins*/		{
										"Skyrim.esm", 
										"Update.esm",
										"Dawnguard.esm", 
										"HearthFires.esm",
										"Dragonborn.esm"
									},
		/*steamAppIds*/				{489830}
	};

	using GamesMap = unordered_map<Game::GameId, Game>;

	GamesMap games = {
		{Oblivion.id, Oblivion},
		{Fallout3.id, Fallout3},
		{FalloutNV.id, FalloutNV},
		{Skyrim.id, Skyrim},
		{Fallout4.id, Fallout4},
		{SkyrimSE.id, SkyrimSE}
	};
}