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

#ifndef EQGAMESCANNER_H
#define EQGAMESCANNER_H

#include <string>
#include <fstream>
#include <windows.h> // Provides "Windows Style" Type Definitions

class EQGameScanner
{
public:
	EQGameScanner(std::string pathToExecutable);
	~EQGameScanner();

public:
	bool executableExists() const;

	template <typename T>
	T findEQPointerOffset(DWORD startAddress, std::size_t blockSize, const PBYTE byteMask, const PCHAR charMask);
	template <typename T>
	T findEQStructureOffset(DWORD startAddress, std::size_t blockSize, const PBYTE byteMask, const PCHAR charMask, const DWORD baseEQPointerAddress);

private:
	bool compareData(PBYTE data, PBYTE byteMask, PCHAR charMask);

private:
	std::ifstream file;
	std::string executablePath;
};

#include "EQGameScanner.cpp"

#endif // EQGAMESCANNER_H
