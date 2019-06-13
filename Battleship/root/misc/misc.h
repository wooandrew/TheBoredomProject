// TheBoredomProject: Battleship (c)Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#pragma once

#ifndef MISC_FUNCTIONS
#define MISC_FUNCTIONS

#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>
#include <mutex>

#include <GLFW/src/glfw3.h>

namespace Utilities {

	static std::mutex mu;

	static double deltaTime = 0;
	static double lastTime = 0;

	std::string GetDateTime();

	template<typename T>
	void Logger(T override, bool dt = false) {

		std::lock_guard<std::mutex> lock(mu);

		if (dt) {
			std::cerr << GetDateTime() << " |    | " << override << std::endl;
		}
		else {
			std::cerr << override << std::endl;
		}
	}

	template<typename EN, typename EMSG>
	void Logger(EN err, EMSG emsg) {

		std::lock_guard<std::mutex> lock(mu);
		std::cerr << GetDateTime() << " |" << err << "| " << emsg << std::endl;
	}

	double GetDeltaTime();
	void UpdateDeltaTime();
}

#endif // !MISC_FUNCTIONS