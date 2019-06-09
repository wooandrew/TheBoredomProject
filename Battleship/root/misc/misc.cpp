// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#include "misc.h"

namespace Misc {

	std::string Misc::GetDateTime() {

		auto timeNow = std::chrono::system_clock::now();
		time_t timeNow_t = std::chrono::system_clock::to_time_t(timeNow);

		#pragma warning(disable: 4996)	// MSVC only -> "std::localtime" is considered unsafe, uses localtime_s instead.
		std::stringstream toString;
		toString << std::put_time(std::localtime(&timeNow_t), "%Y/%m/%d _ %T");

		return toString.str();
	}

	double GetDeltaTime() {
		return deltaTime;
	}

	void UpdateDeltaTime() {

		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
	}
}
