#include "kb_cv_string.h"

void kb::stringF::putText(cv::Mat& mat, std::string& str1, cv::Point& pt1) {
	if (m_dup > 0) {
		double f1 = m_fontScale * 2;
		if (f1 < 1.0) { f1 = 1.0; }
		int t1 = m_thickness * f1;
		if (t1 < 3) {
			t1 = 3;
		}
		cv::putText(mat, str1, pt1, m_fontFace, m_fontScale, m_color_bk, m_thickness + t1);
	}
	cv::putText(mat, str1, pt1, m_fontFace, m_fontScale, m_color, m_thickness);
}

void kb::stringF::putText(cv::Mat& mat, cv::Point& pt1) {
	if (m_dup > 0) {
		double f1 = m_fontScale * 2;
		if (f1 < 1.0) { f1 = 1.0; }
		int t1 = m_thickness * f1;
		if (t1 < 3) {
			t1 = 3;
		}

		cv::putText(mat, m_str, pt1, m_fontFace, m_fontScale, m_color_bk, m_thickness + t1);
	}
	cv::putText(mat, m_str, pt1, m_fontFace, m_fontScale, m_color, m_thickness);
}

void kb::stringF::putText(cv::Mat& mat) {

	if (m_dup > 0) {
		double f1 = m_fontScale * 2;
		if (f1 < 1.0) { f1 = 1.0; }
		int t1 = m_thickness * f1;
		if (t1 < 3) {
			t1 = 3;
		}

		cv::putText(mat, m_str, m_pt, m_fontFace, m_fontScale, m_color_bk, m_thickness + t1);
	}
	cv::putText(mat, m_str, m_pt, m_fontFace, m_fontScale, m_color, m_thickness);
}
