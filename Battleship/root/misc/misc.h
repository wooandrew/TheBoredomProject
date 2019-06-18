// TheBoredomProject: Battleship (c)Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#pragma once

#ifndef MISC_FUNCTIONS
#define MISC_FUNCTIONS

#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <mutex>

#include <GLFW/src/glfw3.h>

namespace Utilities {

	static std::mutex mu;

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

	template<typename T>
	std::vector<std::string> split(T input, char delimiter = ' ') {

		std::vector<std::string> ret;

		std::ostringstream oss_input;
		oss_input << input;

		std::istringstream iss_input(oss_input.str());
		std::string token;

		while (std::getline(iss_input, token, delimiter)) {
			ret.push_back(token);
		}

		return ret;
	}

	struct DeltaTime {

		DeltaTime() = delete;

		static double GetDeltaTime();
		static void UpdateDeltaTime();

	private:
		static double deltaTime;
		static double lastTime;
	};
}

#endif // !MISC_FUNCTIONS