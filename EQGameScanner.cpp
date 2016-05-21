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

#include <fstream>
#include <string.h>
#include "EQGameScanner.h"

EQGameScanner::EQGameScanner(std::string pathToExecutable)
	: executablePath(pathToExecutable)
{
	// Attempt to open the executable
	file.open(executablePath.c_str(), std::ios::in | std::ios::binary);
}

EQGameScanner::~EQGameScanner(void)
{
	// Close the file before we destroy the object
	if (file)
		file.close();
}

bool EQGameScanner::executableExists() const
{
	return file.is_open();
}

// Thanks to dom1n1k for the piece of code this is based off of.
bool EQGameScanner::compareData(PBYTE data, PBYTE byteMask, PCHAR charMask)
{
	for(; *charMask; ++charMask, ++data, ++byteMask)
	{
        if((*charMask == 'x' || *charMask == 'o') && *data != *byteMask )
            return false;
	}
    return (*charMask) == 0;
}
