// TheBoredomProject: Battleship (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

#include "math.h"

namespace Rect {

	std::ostream& operator<<(std::ostream& os, Rect::XYWH right) {
		os << right.x << " : " << right.y << " : " << right.width << " : " << right.height;
		return os;
	}
}
