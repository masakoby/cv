#include <vector>
#include <opencv2/opencv.hpp>

#pragma once

namespace kb
{
	//	��`�̂S���̓_���擾����
	//		�P���܂킷�`�œ���
	void rect2points(cv::Rect& rect, std::vector<cv::Point2f>& vp);
};
