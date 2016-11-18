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

using std::string;
using std::vector;
using std::tuple;

using std::make_tuple;
using std::random_shuffle;
using std::move;
using std::get;

enum Neighbor {North, East, South, West};


// TODO: reference additional headers your program requires here
