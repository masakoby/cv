#pragma once

namespace kb
{
	//
	inline int round_index(int i, int width)
	{
		if (i < 0) {
			int ii = (i % width);
			if (ii < 0) { ii += width; }
			return ii;
		}
		else if (width <= i) {
			int ii = (i % width);
			return ii;
		}
		return i;
	}

};
