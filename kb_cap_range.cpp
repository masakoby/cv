#include "kb_cap_range.h"


int kb::cap_range(double range[2], double width, double range_out[2])
{
	if (range[0] < -width) {
		range_out[0] = -width;
	}
	else {
		range_out[0] = range[0];
	}
	if (range[1] > width) {
		range_out[1] = width;
	}
	else {
		range_out[1] = range[1];
	}

	return 0;
}
