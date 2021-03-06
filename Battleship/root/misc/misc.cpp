// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Website: https://wooandrew.github.io/
// Email: seungminleader@gmail.com

#include "misc.h"

namespace Utilities {

	std::string Utilities::GetDateTime() {

		auto timeNow = std::chrono::system_clock::now();
		time_t timeNow_t = std::chrono::system_clock::to_time_t(timeNow);

		#pragma warning(disable: 4996)	// MSVC only -> "std::localtime" is considered unsafe, uses localtime_s instead.
		std::stringstream toString;
		toString << std::put_time(std::localtime(&timeNow_t), "%Y/%m/%d _ %T");

		return toString.str();
	}

	double DeltaTime::deltaTime = 0;
	double DeltaTime::lastTime = 0;

	double DeltaTime::GetDeltaTime() {
		return deltaTime;
	}

	void DeltaTime::UpdateDeltaTime() {

		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
	}

	bool DebugConsole::hidden = false;
	bool DebugConsole::showhide = true;

#ifdef _WIN32

#pragma warning(disable: 4005)	// IGNORE APIENTRY REDEFINITION. THIS IS A SELF-DEPRECATED PRAGMA AND SHOULD BE REMOVED.
#include <Windows.h>

	void DebugConsole::EnableShowHide() {
		showhide = true;
	}

	void DebugConsole::e_s_h() {
		EnableShowHide();
	}

	void DebugConsole::DisableShowHide() {
		showhide = false;
	}

	void DebugConsole::d_s_h() {
		DisableShowHide();
	}

	void DebugConsole::AutoShowHide() {

		if (hidden) {
			Show();
		}
		else {
			Hide();
		}
	}

	void DebugConsole::a_s_h() {
		AutoShowHide();
	}

	void DebugConsole::Hide() {

		if (showhide) {
			FreeConsole();
			hidden = true;
		}
	}

	void DebugConsole::Show() {

		if (showhide) {

			AllocConsole();
			system("TITLE Battleship Debug Console");

			hidden = false;
		}
	}

#else

	void DebugConsole::EnableShowHide() {
		showhide = true;
	}

	void DebugConsole::e_s_h() {
		EnableShowHide();
	}

	void DebugConsole::DisableShowHide() {
		showhide = false;
	}

	void DebugConsole::d_s_h() {
		DisableShowHide();
	}

	void DebugConsole::AutoShowHide() {

		Logger("Error: Not Windows.", true);

		//if (hidden) {
		//	Show();
		//}
		//else {
		//	Hide();
		//}
	}

	void DebugConsole::a_s_h() {
		AutoShowHide();
	}

	void DebugConsole::Hide() {

		if (showhide) {
			Logger("Error: Not Windows.", true);
			hidden = true;
		}
	}

	void DebugConsole::Show() {
		
		if (showhide) {
			Logger("Error: Not Windows.", true);
			hidden = false;
		}
	}

#endif
}
