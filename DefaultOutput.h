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

#ifndef DEFAULTOUTPUT_H
#define DEFAULTOUTPUT_H

#include <iostream>
#include <string>
#include <windows.h> // Provides "Windows Style" Type Definitions

typedef void (*DisplayOffsetFunction)(std::string, DWORD);
typedef void (*DisplaySectionNameFunction)(std::string);

namespace DefaultOutput
{
	void displaySectionName(std::string sectionName)
	{
		std::cout << std::endl;
		std::cout << sectionName << std::endl;
		for (std::size_t i = 0; i < sectionName.length(); ++i)
			std::cout << "=";
		std::cout << std::endl << std::endl;
	}

	void displayOffset(std::string offsetName, DWORD offsetValue)
	{
		std::cout << offsetName << ":" << std::endl;
		std::cout << "| Match Found @ " << ((offsetValue == NULL) ? "FALSE" : "TRUE") << std::endl;
		std::cout << "| Offset -> 0x" << std::hex << offsetValue << std::endl;
		std::cout << std::endl;
	}
};

#endif // DEFAULTOUTPUT_H
