#include "kb_cv_fill_hole.h"
#include "kb_cv_labeling.h"

int kb::fill_hole(
	cv::Mat& mat1,
	cv::Mat& mat_out,
	int	square_hole
)
{
	cv::Mat mat2;
	cv::threshold(mat1, mat2, 1.0, 255, cv::THRESH_BINARY_INV);

	cv::Mat matL;
	std::vector<int> squares;
	std::vector<cv::Point2f> centers;
	std::vector<cv::Point> vecPtsMin, vecPtsMax;
	if (kb::labeling_4n(mat2, matL, 0, squares, centers, vecPtsMin, vecPtsMax) < 0)
		return -1;

	cv::Size sz = matL.size();

	std::vector<unsigned char> lut;
	int lnum = squares.size();
	int lnum_fillhole = 0;
	lut.resize(lnum + 1, 0);
	lut[0] = 255;
	for (int i = 1; i <= lnum; i++) {
		if (vecPtsMin[i - 1].x == 0 ||
			vecPtsMin[i - 1].y == 0 ||
			vecPtsMax[i - 1].x == (sz.width - 1) ||
			vecPtsMax[i - 1].y == (sz.height - 1))
			continue;

		if (squares[i - 1] <= square_hole || square_hole < 0) {
			lut[i] = 255;
			lnum_fillhole++;
		}
	}

	mat_out = cv::Mat(sz, CV_8UC1, cv::Scalar(0));
	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			int lb = matL.at<int>(j, i);
			if (lb < 0 || lnum < lb)
				continue;

			mat_out.at<unsigned char>(j, i) = lut[lb];
		}
	}

	return lnum_fillhole;
}
