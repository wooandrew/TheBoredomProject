// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "math.h"

namespace Rect {

	std::ostream& operator<<(std::ostream& os, const Rect::XYWH right) {
		os << right.x << " : " << right.y << " : " << right.width << " : " << right.height;
		return os;
	}

	bool XYWH::CheckCollisionAABB(const XYWH& rect2) {

		if ((x < (rect2.x + rect2.width)) && ((x + width) > rect2.x) &&
		    (y < (rect2.y + rect2.height)) && ((y + height) > rect2.y)) {
			return true;
		}

		return false;
	}
}
