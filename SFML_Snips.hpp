#pragma once


// If SFML hasn't been loaded yet, we should probably do so.

#ifndef SFML_SYSTEM_HPP
#define SFML_SYSTEM_HPP

#include <SFML\System.hpp>

#endif

// Include the Snippets:

#include <BZeps-SFML-Snippets\snippets\gameHandler.hpp>
#include <BZeps-SFML-Snippets\snippets\drawable.hpp>


#ifdef _DEBUG

#include <iostream>
std::cout << "Loaded BZeps-SFML-Snippets, thanks for using them!" << std::endl << "This message will not appear under the 'release' configuration." << std::endl;

#endif