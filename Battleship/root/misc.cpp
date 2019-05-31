// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#include "misc.h"

std::string GetDateTime() {

	auto timeNow = std::chrono::system_clock::now();
	time_t timeNow_t = std::chrono::system_clock::to_time_t(timeNow);

	#pragma warning(disable: 4996)
	std::stringstream toString;
	toString << std::put_time(std::localtime(&timeNow_t), "%Y/%m/%d @ %T");

	return toString.str();
}
