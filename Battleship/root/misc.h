// TheBoredomProject: Battleship (c)Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#pragma once

#ifndef MISC_FUNCTIONS
#define MISC_FUNCTIONS

#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class Misc {

public:
	
	Misc() = delete;
	static std::string GetDateTime();
};


#endif // !MISC_FUNCTIONS