#include "kb_cv_remove_regions.h"
#include "kb_cv_labeling.h"

int kb::remove_regions_8n(
	cv::Mat& mat1,
	cv::Mat& mat8U_out,
	int	squareRemove
)
{

	cv::Size sz = mat1.size();
	mat8U_out = cv::Mat(sz, CV_8U, cv::Scalar(0));

	cv::Mat mat2;
	int numL = kb::labeling_8n(mat1, mat2, squareRemove);
	if (numL < 0)
		return -1;

	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			if (mat2.at<int>(j, i) > 0) {
				mat8U_out.at<unsigned char>(j, i) = 255;
			}
		}
	}

	return 0;
}

