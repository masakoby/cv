#define _USE_MATH_DEFINES
#include <math.h>
#include "kb_cv_arrange_rot.h"

int kb::arrange_rot(std::vector<cv::Point2f>& vp1, std::vector<cv::Point2f>& vp2)
{
	int num = vp1.size();
	std::vector<double> vang;
	vang.resize(num);
	vp2.resize(num);

	cv::Point2f p0(0, 0);
	for (int i = 0; i < num; i++) {
		p0.x += vp1[i].x;
		p0.y += vp1[i].y;
	}
	p0.x = p0.x * 0.25;
	p0.y = p0.y * 0.25;

	for (int i = 0; i < num; i++) {
		vp2[i] = vp1[i] - p0;
	}

	float min_a1 = 0;
	int i_a1 = 0;
	for (int i = 0; i < num; i++) {
		float a1 = vp1[i].dot(vp1[i]);
		if (i == 0) {
			min_a1 = a1;
			i_a1 = 0;
		}
		else {
			if (a1 < min_a1) {
				min_a1 = a1;
				i_a1 = i;
			}
		}
	}

	for (int i = 0; i < num; i++) {
		vang[i] = atan2(vp2[i].y, vp2[i].x);
	}
	std::map<double, cv::Point2f> m1;
	for (int i = 0; i < num; i++) {
		double t = vang[i] - vang[i_a1];

		if (t < 0.0) {
			t += (2.0 * M_PI);
		}
		if (t < 0.0) {
			t += (2.0 * M_PI);
		}
		//vang[i] = t;
		m1[t] = vp1[i];
	}

	std::map<double, cv::Point2f, std::less<double>>::iterator it = m1.begin();
	int i = 0;
	for (; it != m1.end(); it++) {
		vp2[i] = it->second;
		i++;
	}


	return 0;
}
