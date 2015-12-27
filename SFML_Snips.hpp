#pragma once

#ifndef BZSF
#define BZSF

// If SFML hasn't been loaded yet, we should probably do so.

#ifndef SFML_GRAPHICS_HPP

#include <SFML\Graphics.hpp>

#endif

// Include dependencies:

#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <memory>
#include <cassert>
#include <deque>
#include <functional>


// Include the Snippets:

#include <bzsf\snippets\general.hpp>
#include <bzsf\snippets\gameHandler.hpp>
#include <bzsf\snippets\drawable.hpp>
#include <bzsf\snippets\desaturator.hpp>
#include <bzsf\snippets\onScreenLog.hpp>
#include <bzsf\snippets\state.hpp>
#include <bzsf\snippets\stateStack.hpp>
#include <bzsf\snippets\performanceDisplay.hpp>
#include <bzsf\snippets\quadTree.hpp>

#endif