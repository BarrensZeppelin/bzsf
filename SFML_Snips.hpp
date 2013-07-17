#pragma once


// If SFML hasn't been loaded yet, we should probably do so.

#ifndef SFML_SYSTEM_HPP

#include <SFML\System.hpp>

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

namespace bzsf {
	const float PI = 3.14159265359f;
	float DEGTORAD(float deg) {return ((deg * PI) / 180.f);}
	float RADTODEG(float rad) {return ((180.f * rad) / PI);}
}

// Include the Snippets:

#include <BZeps-SFML-Snippets\snippets\general.hpp>
#include <BZeps-SFML-Snippets\snippets\gameHandler.hpp>
#include <BZeps-SFML-Snippets\snippets\drawable.hpp>
#include <BZeps-SFML-Snippets\snippets\desaturator.hpp>
