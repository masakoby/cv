#include "kb_cv_segmentation_by_kmeans_RGB.h"
#include "kb_cv_measure_labeling_regions.h"
#include "kb_mat.h"
#include "kb_cv_labeling.h"

int kb::segmentation_by_kmeans_RGB(cv::Mat& matRGB, cv::Mat& matOut32S, int num_cluster, cv::Mat mask)
{
	cv::Size sz1= matRGB.size();
	cv::Mat data(cv::Size(3, sz1.width * sz1.height), CV_32F);
	cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 50, FLT_EPSILON);

	int ii = 0;
	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			cv::Vec3b a = matRGB.at<cv::Vec3b>(j, i);
			data.at<float>(ii, 0) = a[0];
			data.at<float>(ii, 1) = a[1];
			data.at<float>(ii, 2) = a[2];
			ii++;
		}
	}

	cv::Mat centers, labels;
	double c1=cv::kmeans(data, num_cluster, labels, criteria, 1, cv::KMEANS_PP_CENTERS, centers);

	std::cout << "data: " << data.size() << std::endl;
	std::cout << "compactness: " << c1 << std::endl;
	std::cout << "labels: " << labels.size() << std::endl;
	std::cout << "centers: " << centers.size() << std::endl;

	for (int i = 0; i < num_cluster; i++) {
		std::cout <<i<<": "<< centers.at<float>(i, 0) << "," << centers.at<float>(i, 1) << "," << centers.at<float>(i, 2) << std::endl;
	}

	matOut32S = cv::Mat(sz1, CV_32S);

	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			matOut32S.at<int>(j, i) = labels.at<int>(i + j * sz1.width, 0)+1;
		}
	}


	return 0;
}

int kb::segmentation_by_kmeans_HSV(cv::Mat& matRGB, cv::Mat& matOut32S, int num_cluster, cv::Mat mask)
{
	cv::Mat matHSV;
	cv::cvtColor(matRGB, matHSV, cv::COLOR_BGR2HSV);


	cv::Size szM = mask.size();
	cv::Size sz1 = matRGB.size();


	if (szM.width > 0 && szM.height > 0) {
		int cnt = 0;
		for (int j = 0; j < sz1.height; j++) {
			for (int i = 0; i < sz1.width; i++) {
				if (mask.at<unsigned char>(j, i) > 0)
					cnt++;
			}
		}
		matOut32S = cv::Mat(sz1, CV_32S, cv::Scalar(0));

		cv::Mat data(cv::Size(2, cnt), CV_32F);
		cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 50, FLT_EPSILON);

		{
			int ii = 0;
			for (int j = 0; j < sz1.height; j++) {
				for (int i = 0; i < sz1.width; i++) {
					if (mask.at<unsigned char>(j, i) == 0)
						continue;

					cv::Vec3b a = matHSV.at<cv::Vec3b>(j, i);
					data.at<float>(ii, 0) = a[0];
					data.at<float>(ii, 1) = a[1];
					//data.at<float>(ii, 2) = a[2];
					ii++;
				}
			}
		}

		cv::Mat centers, labels;
		double c1 = cv::kmeans(data, num_cluster, labels, criteria, 1, cv::KMEANS_PP_CENTERS, centers);


		{
			int ii = 0;
			for (int j = 0; j < sz1.height; j++) {
				for (int i = 0; i < sz1.width; i++) {
					if (mask.at<unsigned char>(j, i) == 0)
						continue;
					matOut32S.at<int>(j, i) = labels.at<int>(ii, 0) + 1;
					ii++;
				}
			}
		}
	}
	else {
		cv::Mat data(cv::Size(2, sz1.width * sz1.height), CV_32F);
		cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 50, FLT_EPSILON);

		int ii = 0;
		for (int j = 0; j < sz1.height; j++) {
			for (int i = 0; i < sz1.width; i++) {
				cv::Vec3b a = matHSV.at<cv::Vec3b>(j, i);
				data.at<float>(ii, 0) = a[0];
				data.at<float>(ii, 1) = a[1];
				//data.at<float>(ii, 2) = a[2];
				ii++;
			}
		}
		matOut32S = cv::Mat(sz1, CV_32S, cv::Scalar(0));

		cv::Mat centers, labels;
		double c1 = cv::kmeans(data, num_cluster, labels, criteria, 1, cv::KMEANS_PP_CENTERS, centers);

		std::cout << "data: " << data.size() << std::endl;
		std::cout << "compactness: " << c1 << std::endl;
		std::cout << "labels: " << labels.size() << std::endl;
		std::cout << "centers: " << centers.size() << std::endl;

		for (int i = 0; i < num_cluster; i++) {
			std::cout << i << ": " << centers.at<float>(i, 0) << "," << centers.at<float>(i, 1) << "," << centers.at<float>(i, 2) << std::endl;
		}


		for (int j = 0; j < sz1.height; j++) {
			for (int i = 0; i < sz1.width; i++) {
				matOut32S.at<int>(j, i) = labels.at<int>(i + j * sz1.width, 0) + 1;
			}
		}
	}


	return 0;
}

int kb::segmentation_by_kmeans_Gray(cv::Mat& matRGB, cv::Mat& matOut32S, int num_cluster, cv::Mat mask)
{
	cv::Size szM=mask.size();
	cv::Mat matG;
	cv::cvtColor(matRGB, matG, cv::COLOR_BGR2GRAY);
	cv::Size sz1 = matRGB.size();


	if (szM.width > 0 && szM.height > 0) {
		int cnt = 0;
		for (int j = 0; j < sz1.height; j++) {
			for (int i = 0; i < sz1.width; i++) {
				if (mask.at<unsigned char>(j, i) > 0)
					cnt++;
			}
		}
		matOut32S = cv::Mat(sz1, CV_32S, cv::Scalar(0));

		if (cnt == 0)
			return -1;

		cv::Mat data(cv::Size(1, cnt), CV_32F);
		cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 50, FLT_EPSILON);

		{
			int ii = 0;
			for (int j = 0; j < sz1.height; j++) {
				for (int i = 0; i < sz1.width; i++) {
					if (mask.at<unsigned char>(j, i) == 0)
						continue;

					data.at<float>(ii, 0) = matG.at<unsigned char>(j, i);
					ii++;
				}
			}
		}

		cv::Mat centers, labels;
		double c1 = cv::kmeans(data, num_cluster, labels, criteria, 1, cv::KMEANS_PP_CENTERS, centers);

		//std::cout << "data: " << data.size() << std::endl;
		//std::cout << "compactness: " << c1 << std::endl;
		//std::cout << "labels: " << labels.size() << std::endl;
		//std::cout << "centers: " << centers.size() << std::endl;

		//for (int i = 0; i < num_cluster; i++) {
		//	std::cout << i << ": " << centers.at<float>(i, 0) << "," << centers.at<float>(i, 1) << "," << centers.at<float>(i, 2) << std::endl;
		//}


		{
			int ii = 0;
			for (int j = 0; j < sz1.height; j++) {
				for (int i = 0; i < sz1.width; i++) {
					if (mask.at<unsigned char>(j, i) == 0)
						continue;

					matOut32S.at<int>(j, i) = labels.at<int>(ii, 0) + 1;
					ii++;
				}
			}
		}

	}
	else {


		cv::Mat data(cv::Size(1, sz1.width * sz1.height), CV_32F);
		cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 50, FLT_EPSILON);

		int ii = 0;
		for (int j = 0; j < sz1.height; j++) {
			for (int i = 0; i < sz1.width; i++) {
				data.at<float>(ii, 0) = matG.at<unsigned char>(j, i);
				ii++;
			}
		}

		cv::Mat centers, labels;
		double c1 = cv::kmeans(data, num_cluster, labels, criteria, 1, cv::KMEANS_PP_CENTERS, centers);

		//std::cout << "data: " << data.size() << std::endl;
		//std::cout << "compactness: " << c1 << std::endl;
		//std::cout << "labels: " << labels.size() << std::endl;
		//std::cout << "centers: " << centers.size() << std::endl;

		//for (int i = 0; i < num_cluster; i++) {
		//	std::cout << i << ": " << centers.at<float>(i, 0) << "," << centers.at<float>(i, 1) << "," << centers.at<float>(i, 2) << std::endl;
		//}

		matOut32S = cv::Mat(sz1, CV_32S);

		for (int j = 0; j < sz1.height; j++) {
			for (int i = 0; i < sz1.width; i++) {
				matOut32S.at<int>(j, i) = labels.at<int>(i + j * sz1.width, 0) + 1;
			}
		}
	}

	return 0;
}

int kb::remove_background_region(cv::Mat& mat32S, int num_label,cv::Mat& matRGB,  cv::Scalar bk_color, cv::Mat& mat8U)
{
	cv::Size sz1 = mat32S.size();

	std::vector<int> vecSquare;
	std::vector<double> vecAverageRGB;
	kb::measureAverage_RGB(mat32S, num_label, matRGB, vecSquare, vecAverageRGB);
	double v2[3] = { bk_color[0],bk_color[1],bk_color[2] };
	int i_min = 0;
	double d12_min = 0;
	for (int i = 0; i < 3; i++) {
		double v1[3] = {
			vecAverageRGB[i * 3 + 0], vecAverageRGB[i * 3 + 1], vecAverageRGB[i * 3 + 2]
		};
		double d12 = kb::frobenius_norm(v1, v2, 3);
		if (i == 0) {
			d12_min = d12;
		}
		else {
			if (d12 < d12_min) {
				d12_min = d12;
				i_min = i;
			}
		}
	}

	mat8U=cv::Mat(sz1, CV_8U, cv::Scalar(0));
	for (int j = 0; j < sz1.height; j++) {
		for (int i = 0; i < sz1.width; i++) {
			int label = mat32S.at<int>(j, i);
			if (label <= 0)
				continue;
			if (label == (i_min + 1))
				continue;

			mat8U.at<unsigned char>(j, i) = 255;
		}
	}

	return 0;
}
