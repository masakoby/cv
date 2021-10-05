#include "kb_cv_drawMatches.h"

//	‘Î‰ž“_‚Ì‰ÂŽ‹‰»
void kb::drawMatches(
	cv::Mat& mat1,
	cv::Mat& mat2,
	std::vector<cv::Point2f>& mp1,
	std::vector<cv::Point2f>& mp2,
	cv::Mat& matV12,
	double ratio_reduce
	)
{
	std::vector<cv::DMatch> v_dm;
	std::vector<cv::KeyPoint> v_kp1, v_kp2;
	int num_1 = mp1.size();
	int num_2 = mp2.size();
	if (num_1 != num_2) {
		std::cout << "error: kb::drawMatches(): input point number: " << num_1 << " " << num_2 << std::endl;
	}

	//	0.1ˆÈ‰º‚Ì‚Æ‚«‚Í”{—¦‚Í•ÏX‚µ‚È‚¢
	if (ratio_reduce < 0.1) {
		if (num_1 == num_2) {
			for (int i = 0; i < num_1; i++) {
				cv::KeyPoint kp1, kp2;
				cv::DMatch dm;
				kp1.pt = mp1[i];
				kp2.pt = mp2[i];
				dm.queryIdx = i;
				dm.trainIdx = i;
				v_kp1.push_back(kp1);
				v_kp2.push_back(kp2);
				v_dm.push_back(dm);
			}
		}

		cv::drawMatches(
			mat1, v_kp1,
			mat2, v_kp2,
			v_dm, matV12,
			cv::Scalar_<double>::all(-1),
			cv::Scalar_<double>::all(-1),
			std::vector<char>(),
			cv::DrawMatchesFlags::DEFAULT);
	}
	else {
		cv::Size sz1 = mat1.size();
		cv::Size sz2 = mat2.size();

		cv::Size sz1m(sz1.width* ratio_reduce, sz1.height * ratio_reduce);
		cv::Size sz2m(sz2.width * ratio_reduce, sz2.height * ratio_reduce);

		cv::Mat mat1m, mat2m;
		cv::resize(mat1, mat1m, sz1m);
		cv::resize(mat2, mat2m, sz2m);

		//
		if (num_1 == num_2) {
			for (int i = 0; i < num_1; i++) {
				cv::KeyPoint kp1, kp2;
				cv::DMatch dm;
				kp1.pt = mp1[i]* ratio_reduce;
				kp2.pt = mp2[i]* ratio_reduce;
				dm.queryIdx = i;
				dm.trainIdx = i;
				v_kp1.push_back(kp1);
				v_kp2.push_back(kp2);
				v_dm.push_back(dm);
			}
		}

		cv::drawMatches(
			mat1m, v_kp1,
			mat2m, v_kp2,
			v_dm, matV12,
			cv::Scalar_<double>::all(-1),
			cv::Scalar_<double>::all(-1),
			std::vector<char>(),
			cv::DrawMatchesFlags::DEFAULT);
	}
}
