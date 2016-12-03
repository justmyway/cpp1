// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

#include "ConsoleWriter.h"
#include "ConsoleReader.h"

using std::string;
using std::vector;
using std::tuple;

using std::make_tuple;
using std::random_shuffle;
using std::move;
using std::get;
using std::to_string;

enum Neighbor {North, East, South, West};

inline const char* ToString(Neighbor v)
{
	switch (v)
	{
	case North:		return "North";
	case East:		return "East";
	case South:		return "South";
	case West:		return "West";
	default:		return "None";
	}
}

inline const int ToInt(string v)
{
	return atoi(v.c_str());
}

constexpr unsigned int Str2Int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (Str2Int(str, h + 1) * 33) ^ str[h];
}
