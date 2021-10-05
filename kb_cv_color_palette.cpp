#include "kb_cv_color_palette.h"
#include "kb_color_palette.h"

int kb::palette_bar(cv::Mat& matRGB, int type)
{
	int num = 500;
	cv::Size sz(100, num);
	matRGB = cv::Mat(sz, CV_8UC3);

	unsigned char prr[500], pgg[500], pbb[500];
	if (type == 0) {
		kb::makeTemparaturePalette(num, prr, pgg, pbb);
	}
	else if (type == 1) {
		kb::makeTemparaturePalette2(num, prr, pgg, pbb);
	}
	else if (type == 2) {
		kb::makeTemparaturePalette3(num, prr, pgg, pbb);
	}
	else if (type == 3) {
		kb::makeRedAndBluePalette(num, prr, pgg, pbb);
	}
	else if (type == 4) {
		kb::makeRedAndBluePalette2(num, prr, pgg, pbb);
	}
	else if (type == 5) {
		kb::makeTemparaturePalette4(num, prr, pgg, pbb);
	}
	else if (type == 6) {
		kb::makeTemparaturePalette0(num, prr, pgg, pbb);
	}

	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			matRGB.at<cv::Vec3b>(j, i) = cv::Vec3b(pbb[j], pgg[j], prr[j]);
		}
	}

	return 0;
}

