/*
 * This file is part of EasyRPG Player.
 *
 * EasyRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EP_EXE_READER_H
#define EP_EXE_READER_H

#include <cstdint>
#include <string>
#include <istream>
#include <vector>
#include "bitmap.h"

/**
 * Extracts resources from an EXE.
 * The istream given is still owned by the parent,
 *  but it is in use by the reader.
 */
class EXEReader {
public:
	// uint32_t is used here as:
	// 1. everywhere else uses "unsigned", which is equally as odd...
	// 2. max offset value is this size

	EXEReader(std::istream& core);
	~EXEReader();

	// Extracts an EXFONT resource with BMP header if present
	// and returns exfont buffer on success.
	std::vector<uint8_t> GetExFont();
private:
	// Bounds-checked unaligned reader primitives.
	// In case of out-of-bounds, returns 0 - this will usually result in a harmless error at some other level,
	//  or a partial correct interpretation.
	uint8_t GetU8(uint32_t point);
	uint16_t GetU16(uint32_t point);
	uint32_t GetU32(uint32_t point);

	bool ResNameCheck(uint32_t namepoint, const char* name);

	// 0 if resource section was unfindable.
	uint32_t resource_ofs;
	uint32_t resource_rva;

	std::istream& corefile;
};

#endif
