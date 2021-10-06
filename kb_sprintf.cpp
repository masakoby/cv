#include "kb_sprintf.h"


void kb::doulbe2string(double val, int digit_num, std::string& str1)
{
	char buf[128];

	if (digit_num < 0)
		digit_num = 0;

	switch (digit_num) {
	case 0:
		sprintf_s(buf, 128, "%.0f", val);
		break;
	case 1:
		sprintf_s(buf, 128, "%.1f", val);
		break;
	case 2:
		sprintf_s(buf, 128, "%.2f", val);
		break;
	case 3:
		sprintf_s(buf, 128, "%.3f", val);
		break;
	case 4:
		sprintf_s(buf, 128, "%.4f", val);
		break;
	case 5:
		sprintf_s(buf, 128, "%.5f", val);
		break;
	case 6:
		sprintf_s(buf, 128, "%.6f", val);
		break;
	case 7:
		sprintf_s(buf, 128, "%.7f", val);
		break;
	case 8:
		sprintf_s(buf, 128, "%.8f", val);
		break;
	case 9:
		sprintf_s(buf, 128, "%.9f", val);
		break;
	case 10:
		sprintf_s(buf, 128, "%.10f", val);
		break;
	default:
		sprintf_s(buf, 128, "%f", val);
		break;
	}
	str1 = buf;
}
