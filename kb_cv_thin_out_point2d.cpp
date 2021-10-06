#include "kb_cv_thin_out_point2d.h"

//	‚QŽŸŒ³“_ŒQ‚ðŠÔˆø‚­
int kb::thin_out_point2d(
	std::vector<cv::Point2f>& vpt_in,
	std::vector<int>& vidx_out,
	float width
)
{
	int num1 = vpt_in.size();
	if (num1 <= 0)
		return -1;
	if (width < 1.0E-6)
		return -1;

	int64 range_x[2] = { vpt_in[0].x / width, 	vpt_in[0].x / width };
	int64 range_y[2] = { vpt_in[0].y / width, 	vpt_in[0].y / width };
	for (int i = 1; i < num1; i++) {
		int64 x1 = vpt_in[i].x / width;
		int64 y1 = vpt_in[i].y / width;

		if (x1 < range_x[0]) {
			range_x[0] = x1;
		}
		if (range_x[1] < x1) {
			range_x[1] = x1;
		}
		if (y1 < range_y[0]) {
			range_y[0] = y1;
		}
		if (range_y[1] < y1) {
			range_y[1] = y1;
		}
	}

	int64 wx = range_x[1] - range_x[0] + 1;
	int64 wy = range_y[1] - range_y[0] + 1;

	std::cout << wx << " " << wy << std::endl;
	// 
	if (wx > 100000 || wy > 100000)
		return -1;

	std::vector<unsigned char> flags;
	flags.resize(wx * wy, 0);


	for (int i = 0; i < num1; i++) {
		int64 x1 = (int64)(vpt_in[i].x / width) - range_x[0];
		int64 y1 = (int64)(vpt_in[i].y / width) - range_y[0];

		if (flags[x1 + y1 * wx] == 0) {
			flags[x1 + y1 * wx] = 1;
			vidx_out.push_back(i);
		}
	}

	return 0;
}

//	‚QŽŸŒ³“_ŒQ‚ðŠÔˆø‚­
int kb::thin_out_point2d(
	std::vector<cv::Point2f>& vpt_in,
	std::vector<cv::Point2f>& vpt_out,
	float width
)
{
	std::vector<int> vidx;
	if (kb::thin_out_point2d(vpt_in, vidx, width) < 0)
		return -1;
	int num1 = vidx.size();
	vpt_out.resize(num1);
	for (int i = 0; i < num1; i++) {
		vpt_out[i] = vpt_in[vidx[i]];
	}

	return 0;
}