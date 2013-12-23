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
#include <vector>
#include <map>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <memory>
#include <cassert>
#include <deque>


// Include the Snippets:

#include <BZeps-SFML-Snippets\snippets\general.hpp>
#include <BZeps-SFML-Snippets\snippets\gameHandler.hpp>
#include <BZeps-SFML-Snippets\snippets\drawable.hpp>
#include <BZeps-SFML-Snippets\snippets\desaturator.hpp>
#include <BZeps-SFML-Snippets\snippets\onScreenLog.hpp>

#endif