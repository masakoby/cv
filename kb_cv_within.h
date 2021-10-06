#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	inline int within(cv::Rect& rect, cv::Point pt) {
		if (rect.x <= pt.x && rect.y <= pt.y && pt.x < (rect.x + rect.width) && pt.y < (rect.y + rect.height)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	inline int within(cv::Size& sz, cv::Point pt) {
		if (0 <= pt.x && 0 <= pt.y && pt.x < sz.width && pt.y < sz.height) {
			return 1;
		}
		else {
			return 0;
		}
	}
	inline int within(cv::Size& sz, int x, int y) {
		if (0 <= x && 0 <= y && x < sz.width && y < sz.height) {
			return 1;
		}
		else {
			return 0;
		}
	}

	inline void convert_within(cv::Size& sz, int& x1, int& y1) {
		if (x1 < 0) {
			x1 = 0;
		}
		else if (sz.width <= x1) {
			x1 = sz.width - 1;
		}
		if (y1 < 0) {
			y1 = 0;
		}
		else if (sz.height <= y1) {
			y1 = sz.height - 1;
		}
	}

};