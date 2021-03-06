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
#include "windows.h" // Provides "Windows Style" Type Definitions

class EQGameScanner
{
public:
	EQGameScanner(std::string pathToExecutable);
	~EQGameScanner();

public:
	bool executableExists() const;

    template <typename T>
    T findEQPointerOffset(DWORD startAddress, std::size_t blockSize, const PBYTE byteMask, const PCHAR charMask)
    {
        // If the file can't be opened (or doesn't exist), return NULL for pointer offset.
        if (!file)
            return 0;

        // Setup our temporary storage variables
        PBYTE buffer = new BYTE[blockSize];
        DWORD matchAddr = 0;

        // I like clean memory.
        memset(buffer, 0, blockSize);

        // Move get pointer to the start of the block we want to search
        // Then attempt to read blockSize to the buffer
        file.seekg(startAddress, std::ios::beg);
        file.read((char *)buffer, blockSize);

        // Search for a position that fits our masks in memory.
        // Thanks to dom1n1k for the piece of code this is based off of.
        for (DWORD i = 0; i < blockSize; ++i)
        {
            if (compareData(buffer + i, byteMask, charMask))
            {
                matchAddr = i;
                break;
            }
        }

        // If we didn't find a match, return NULL
        if (matchAddr == 0)
            return 0;

        // Find where our target address we're searching for is stored, and return its value.
        T nRet = *reinterpret_cast<T*>(buffer + matchAddr + std::string(charMask).find_first_of("t"));
        delete[] buffer;

        return nRet;
    }

    template <typename T>
    T findEQStructureOffset(DWORD startAddress, std::size_t blockSize, const PBYTE byteMask, const PCHAR charMask, const DWORD baseEQPointerAddress)
    {
        // Create a new, editable, copy of byteMask.
        PBYTE newByteMask = new BYTE[strlen(charMask)];
        memcpy(newByteMask, byteMask, strlen(charMask));

        // Replace the EQPointer in our byteMask with the EQPointer given as an argument.
        // The location of the EQPointer is denoted by the letter o in our character mask.
        // Currently we require and always assume that the EQPointer is 4 bytes.
        PDWORD valueToChange = reinterpret_cast<PDWORD>(newByteMask + std::string(reinterpret_cast<const PCHAR>(charMask)).find_first_of("o"));
        *valueToChange = baseEQPointerAddress;

        // Use the updated byteMask to locate the EQStructureOffset
        T nRet = findEQPointerOffset<T>(startAddress, blockSize, newByteMask, charMask);
        delete[] newByteMask;

        return nRet;
    }


private:
	bool compareData(PBYTE data, PBYTE byteMask, PCHAR charMask);

private:
	std::ifstream file;
	std::string executablePath;
};

#endif // EQGAMESCANNER_H
