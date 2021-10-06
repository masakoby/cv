#include <opencv2/opencv.hpp>

namespace kb
{
	struct stringF
	{
		stringF()
		{
			m_fontFace = cv::FONT_HERSHEY_SIMPLEX;
			m_fontScale = 0.6;
			m_thickness = 1;
			m_color = cv::Scalar(0, 0, 255);
			m_color_bk = cv::Scalar(255, 255, 255);
			m_pt = cv::Point(0, 0);
			m_dup = 0;
		}

		stringF(double fontScale, int thickness, cv::Scalar color)
		{
			m_fontScale = fontScale;
			m_thickness = thickness;
			m_color = color;
		}

	public:
		//	•¶Žš
		int m_fontFace;
		double m_fontScale;
		int m_thickness;
		cv::Scalar m_color;

		int m_dup;
		cv::Scalar m_color_bk;

		std::string m_str;
		cv::Point m_pt;

		void putText(cv::Mat& mat, std::string& str1, cv::Point& pt1);
		void putText(cv::Mat& mat, cv::Point& pt1);
		void putText(cv::Mat& mat);
	};
};
