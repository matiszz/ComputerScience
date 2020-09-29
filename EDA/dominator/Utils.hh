#ifndef Utils_hh
#define Utils_hh

#include <cassert>
#include <cstdlib>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;


/** \file
 * Contains several useful includes, plus defines for errors.
 */


/**
 * Assert with message.
 */
#define _my_assert(b, s) { if (not (b)) { cerr << "ERROR: " << s << endl; assert(b); } }


/**
 * Macro to specifically indicate when some code is unreachable,
 * so that the compiler doesn't cry when using NDEBUG.
 */
#define _unreachable() { _my_assert(false, "Unreachable code reached."); }


#endif
