/* 
 * Smart EQ Offset Finder - GPL Edition
 * Copyright 2007-2009, Carpathian <Carpathian01@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib> // Provides EXIT_SUCCESS
#include <iostream>
#include "EQGameScanner.h"
#include "EQGamePatterns.h"


/*
 * Output Functions
 */
#include "DefaultOutput.h"
#include "MySEQOutput.h"
DisplaySectionNameFunction displaySectionName = &DefaultOutput::displaySectionName;
DisplayOffsetFunction displayOffset = &DefaultOutput::displayOffset;


/*
 * Offset Value Storage
 */
namespace EQPrimaryOffsets
{
	DWORD Zone = 0x0;
	DWORD ZoneInfo = 0x0;
	DWORD SpawnHeader = 0x0;
	DWORD CharInfo = 0x0;
	DWORD Items = 0x0;
	DWORD Target = 0x0;
	DWORD World = 0x0;
};

namespace EQSpawnInfoOffsets
{
	DWORD Next = 0x0;
	DWORD Prev = 0x0;
	DWORD Lastname = 0x0;
	DWORD X = 0x0;
	DWORD Y = 0x0;
	DWORD Z = 0x0;
	DWORD Speed = 0x0;
	DWORD Heading = 0x0;
	DWORD Name = 0x0;
	DWORD Type = 0x0;
	DWORD SpawnId = 0x0;
	DWORD Hide = 0x0;
	DWORD Level = 0x0;
	DWORD Race = 0x0;
	DWORD Class = 0x0;
};


/*
 * Primary Offsets Search Driver
 */
void findPrimaryOffsets(EQGameScanner& scanner)
{
	// Primary Offsets
	displaySectionName("Primary Offsets");

	// ZoneAddr
	EQPrimaryOffsets::Zone = scanner.findEQPointerOffset<DWORD>(startZoneAddr, 0x100000, patternZoneAddr, maskZoneAddr);
	displayOffset("ZoneAddr", EQPrimaryOffsets::Zone);

	// ZoneInfoAddr
	EQPrimaryOffsets::ZoneInfo = scanner.findEQPointerOffset<DWORD>(startZoneInfoAddr, 0x100000, patternZoneInfoAddr, maskZoneInfoAddr);
	displayOffset("ZoneInfoAddr", EQPrimaryOffsets::ZoneInfo);

	// SpawnHeaderAddr
	EQPrimaryOffsets::SpawnHeader = scanner.findEQPointerOffset<DWORD>(startSpawnHeaderAddr, 0x100000, patternSpawnHeaderAddr, maskSpawnHeaderAddr);
	displayOffset("SpawnHeaderAddr", EQPrimaryOffsets::SpawnHeader);

	// CharInfoAddr
	EQPrimaryOffsets::CharInfo = scanner.findEQPointerOffset<DWORD>(startCharInfoAddr, 0x100000, patternCharInfoAddr, maskCharInfoAddr);
	displayOffset("CharInfoAddr", EQPrimaryOffsets::CharInfo);

	// ItemsAddr
	EQPrimaryOffsets::Items = scanner.findEQPointerOffset<DWORD>(startItemsAddr, 0x100000, patternItemsAddr, maskItemsAddr);
	displayOffset("ItemsAddr", EQPrimaryOffsets::Items);

	// TargetAddr
	EQPrimaryOffsets::Target = scanner.findEQPointerOffset<DWORD>(startTargetAddr, 0x100000, patternTargetAddr, maskTargetAddr);
	displayOffset("TargetAddr", EQPrimaryOffsets::Target);

	// WorldAddr
	EQPrimaryOffsets::World = scanner.findEQPointerOffset<DWORD>(startWorldAddr, 0x100000, patternWorldAddr, maskWorldAddr);
	displayOffset("WorldAddr", EQPrimaryOffsets::World);
}


/*
 * SpawnInfo Offsets Search Driver
 */
void findSpawnInfoOffsets(EQGameScanner& scanner)
{
	// Primary Offsets
	displaySectionName("SpawnInfo Offsets");

	// SpawnInfo::Next
	EQSpawnInfoOffsets::Next = scanner.findEQStructureOffset<BYTE>(startSpawnInfoNextAddr, 0x100000, patternSpawnInfoNextAddr, maskSpawnInfoNextAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("NextOffset", EQSpawnInfoOffsets::Next);

	// SpawnInfo::X
	EQSpawnInfoOffsets::X = scanner.findEQStructureOffset<BYTE>(startSpawnInfoXAddr, 0x100000, patternSpawnInfoXAddr, maskSpawnInfoXAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("XOffset", EQSpawnInfoOffsets::X);

	// SpawnInfo::Y
	EQSpawnInfoOffsets::Y = scanner.findEQStructureOffset<BYTE>(startSpawnInfoYAddr, 0x100000, patternSpawnInfoYAddr, maskSpawnInfoYAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("YOffset", EQSpawnInfoOffsets::Y);

	// SpawnInfo::Z
	EQSpawnInfoOffsets::Z = scanner.findEQStructureOffset<BYTE>(startSpawnInfoZAddr, 0x100000, patternSpawnInfoZAddr, maskSpawnInfoZAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("ZOffset", EQSpawnInfoOffsets::Z);

	// SpawnInfo::Speed
	EQSpawnInfoOffsets::Speed = scanner.findEQStructureOffset<BYTE>(startSpawnInfoSpeedAddr, 0x100000, patternSpawnInfoSpeedAddr, maskSpawnInfoSpeedAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("SpeedOffset", EQSpawnInfoOffsets::Speed);

	// SpawnInfo::Heading
	EQSpawnInfoOffsets::Heading = scanner.findEQStructureOffset<DWORD>(startSpawnInfoHeadingAddr, 0x100000, patternSpawnInfoHeadingAddr, maskSpawnInfoHeadingAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("HeadingOffset", EQSpawnInfoOffsets::Heading);

	// SpawnInfo::Name
	EQSpawnInfoOffsets::Name = scanner.findEQStructureOffset<DWORD>(startSpawnInfoNameAddr, 0x100000, patternSpawnInfoNameAddr, maskSpawnInfoNameAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("NameOffset", EQSpawnInfoOffsets::Name);

	// SpawnInfo::Type
	EQSpawnInfoOffsets::Type = scanner.findEQStructureOffset<DWORD>(startSpawnInfoTypeAddr, 0x100000, patternSpawnInfoTypeAddr, maskSpawnInfoTypeAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("TypeOffset", EQSpawnInfoOffsets::Type);

	// SpawnInfo::SpawnId
	EQSpawnInfoOffsets::SpawnId = scanner.findEQStructureOffset<DWORD>(startSpawnInfoSpawnIdAddr, 0x100000, patternSpawnInfoSpawnIdAddr, maskSpawnInfoSpawnIdAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("SpawnIdOffset", EQSpawnInfoOffsets::SpawnId);

	// SpawnInfo::Hide
	EQSpawnInfoOffsets::Hide = scanner.findEQStructureOffset<DWORD>(startSpawnInfoHideAddr, 0x100000, patternSpawnInfoHideAddr, maskSpawnInfoHideAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("HideOffset", EQSpawnInfoOffsets::Hide);

	// SpawnInfo::Level
	EQSpawnInfoOffsets::Level = scanner.findEQStructureOffset<DWORD>(startSpawnInfoLevelAddr, 0x100000, patternSpawnInfoLevelAddr, maskSpawnInfoLevelAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("LevelOffset", EQSpawnInfoOffsets::Level);

	// SpawnInfo::Race
	EQSpawnInfoOffsets::Race = scanner.findEQStructureOffset<DWORD>(startSpawnInfoRaceAddr, 0x100000, patternSpawnInfoRaceAddr, maskSpawnInfoRaceAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("RaceOffset", EQSpawnInfoOffsets::Race);

	// SpawnInfo::Class
	EQSpawnInfoOffsets::Class = scanner.findEQStructureOffset<DWORD>(startSpawnInfoClassAddr, 0x100000, patternSpawnInfoClassAddr, maskSpawnInfoClassAddr, EQPrimaryOffsets::CharInfo);
	displayOffset("ClassOffset", EQSpawnInfoOffsets::Class);
}


/*
 * Main Application Driver
 */
int main(int argc, char *argv[])
{
	std::cout << "# Smart EQ Offset Finder v0.9.1 (GPL Edition)" << std::endl;
	std::cout << "# Copyright 2007-2009, Carpathian <Carpathian01@gmail.com>" << std::endl << std::endl;

	// If the user doesn't provide an argument, we default to eqgame.exe
	std::string executablePath = "eqgame.exe";
	if (argc > 1)
	{
		if (strcmp(argv[1], "-h") == 0)
		{
			// The filename is kept as the same argument
			std::cout << "Usage: smarteqoffsets.exe [filename] [-myseq]" << std::endl;
			return EXIT_SUCCESS;
		}
		else {
			executablePath = argv[1];

			// Outputs the results MySEQ style
			if (argc >= 3 && argv[2] == "-myseq")
			{
				displayOffset = &MySEQOutput::displayOffset;
				displaySectionName = &MySEQOutput::displaySectionName;
			}
		}
	}

	// Initialize the EQGameScanner class against the given path.
	EQGameScanner scanner(executablePath);
	if (!scanner.executableExists())
	{
		std::cerr << "Error: Could not locate the specified executable file." << std::endl;
		return EXIT_FAILURE;
	}

	// Find the offsets...
	findPrimaryOffsets(scanner);
	findSpawnInfoOffsets(scanner);

	std::cin.get();

	return EXIT_SUCCESS;
}