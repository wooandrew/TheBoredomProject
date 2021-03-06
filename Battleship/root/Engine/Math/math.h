// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#pragma once

#ifndef ENGINE_MATH
#define ENGINE_MATH

#include "../../lib.h"

namespace Rect {

	struct XYWH {

		friend std::ostream& operator<<(std::ostream& os, const Rect::XYWH right);

		float x;
		float y;
		float width;
		float height;

		bool CheckCollisionAABB(const XYWH& rect2);
	};
}

#endif // !ENGINE_MATH
