
#include "kb_cv_calib.h"
#include "kb_inifile.h"
#include "kb_searchfiles.h"
#include "kb_cv_equalize_histogram.h"

int kb::read(std::string& path_prm, cv::CirclesGridFinderParameters& prm)
{
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "minDensity", prm.minDensity);
	float dx = 8;
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "densityNeighborhoodSize", dx);
	prm.densityNeighborhoodSize = cv::Size2f(dx, dx);
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "minDistanceToAddKeypoint", prm.minDistanceToAddKeypoint);
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "kmeansAttempts", prm.kmeansAttempts);
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "keypointScale", prm.keypointScale);
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "convexHullFactor", prm.convexHullFactor);

	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "minGraphConfidence", prm.minGraphConfidence);
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "vertexGain", prm.vertexGain);
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "vertexPenalty", prm.vertexPenalty);

	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "edgeGain", prm.edgeGain);
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "edgePenalty", prm.edgePenalty);
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "existingVertexGain", prm.existingVertexGain);
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "minRNGEdgeSwitchDist", prm.minRNGEdgeSwitchDist);

	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "squareSize", prm.squareSize);
	kb::read(path_prm.c_str(), "CirclesGridFinderParameters", "maxRectifiedDistance", prm.maxRectifiedDistance);

	return 0;
}

int kb::read(std::string& path_prm, cv::SimpleBlobDetector::Params& prm)
{
	kb::read(path_prm.c_str(), "SimpleBlobDetector", "minCircularity", prm.minCircularity);
	kb::read(path_prm.c_str(), "SimpleBlobDetector", "maxCircularity", prm.maxCircularity);
	{
		int a = prm.filterByCircularity;
		kb::read(path_prm.c_str(), "SimpleBlobDetector", "filterByCircularity", a);
		prm.filterByCircularity = a;
	}

	kb::read(path_prm.c_str(), "SimpleBlobDetector", "minArea", prm.minArea);
	kb::read(path_prm.c_str(), "SimpleBlobDetector", "maxArea", prm.maxArea);
	{
		int a = prm.filterByArea;
		kb::read(path_prm.c_str(), "SimpleBlobDetector", "filterByArea", a);
		prm.filterByArea = a;
	}

	kb::read(path_prm.c_str(), "SimpleBlobDetector", "minConvexity", prm.minConvexity);
	kb::read(path_prm.c_str(), "SimpleBlobDetector", "maxConvexity", prm.maxConvexity);
	{
		int a = prm.filterByConvexity;
		kb::read(path_prm.c_str(), "SimpleBlobDetector", "filterByConvexity", a);
		prm.filterByConvexity = a;
	}

	std::cout << "filterByCircularity=" << prm.filterByCircularity << std::endl;
	std::cout << "filterByArea=" << prm.filterByArea << std::endl;
	std::cout << "filterByConvexity=" << prm.filterByConvexity << std::endl;
	std::cout << "filterByColor=" << prm.filterByColor << std::endl;
	std::cout << "filterByInertia=" << prm.filterByInertia << std::endl;

	std::cout << "minThreshold=" << prm.minThreshold << std::endl;
	std::cout << "maxThreshold=" << prm.maxThreshold << std::endl;
	std::cout << "thresholdStep=" << prm.thresholdStep << std::endl;

	std::cout << "minCircularity=" << prm.minCircularity << std::endl;
	std::cout << "maxCircularity=" << prm.maxCircularity << std::endl;
	std::cout << "minArea=" << prm.minArea << std::endl;
	std::cout << "maxArea=" << prm.maxArea << std::endl;
	std::cout << "minConvexity=" << prm.minConvexity << std::endl;
	std::cout << "maxConvexity=" << prm.maxConvexity << std::endl;
	std::cout << "minInertiaRatio=" << prm.minInertiaRatio << std::endl;
	std::cout << "maxInertiaRatio=" << prm.maxInertiaRatio << std::endl;

	return 0;
}


int kb::Calib::findCirclesGrid(cv::Mat& matF, std::vector<cv::Point2f>& v2d_out)
{
	cv::Mat matF2g, matFg;
	cv::cvtColor(matF, matFg, cv::COLOR_BGR2GRAY);
	cv::threshold(matFg, matF2g, 127, 255, cv::THRESH_OTSU);
	{
		cv::Size sz2 = matF2g.size();
		for (int j = 0; j < sz2.height; j++) {
			{
				int i = 0;
				matF2g.at<unsigned char>(j, i) = 255;
			}
			{
				int i = sz2.width - 1;
				matF2g.at<unsigned char>(j, i) = 255;
			}
		}
		for (int i = 0; i < sz2.width; i++) {
			{
				int j = 0;
				matF2g.at<unsigned char>(j, i) = 255;
			}
			{
				int j = sz2.height - 1;
				matF2g.at<unsigned char>(j, i) = 255;
			}
		}
	}
	cv::cvtColor(matF2g, matFg, cv::COLOR_GRAY2BGR);

	
	//cv::namedWindow("corners", cv::WINDOW_NORMAL);
	//cv::imshow("corners", matFg);
	//cv::waitKeyEx(30);
	//cv::imwrite("debug.png", matF2g);


	cv::CirclesGridFinderParameters prm_c = m_prm_c;


	std::vector< cv::CirclesGridFinderParameters> vprm;
	for (int i0 = 0; i0 <= 2; i0++) {
//	for (int i0 = 0; i0 <= 4; i0++) {

		prm_c.minDensity = 5 * std::pow(2.0, i0);

		//for (int i1 = 0; i1 <= 5; i1++) {
		for (int i1 = 0; i1 <= 4; i1++) {
			prm_c.densityNeighborhoodSize.width = 8 * std::pow(2.0, i1);
			prm_c.densityNeighborhoodSize.height = 8 * std::pow(2.0, i1);

			for (int i2 = 1; i2 <= 4; i2++) {
				prm_c.minDistanceToAddKeypoint = 5 * std::pow(2.0, i2);
				for (int i3 = 1; i3 <= 3; i3++) {
					prm_c.minGraphConfidence = std::pow(3.0, i3);
					for (int i4 = 1; i4 <= 2; i4++) {
						prm_c.convexHullFactor = 1.1 * (double)i4;
						for (int i5 = 1; i5 <= 1; i5++) {
							prm_c.keypointScale = i5;
							for (int i6 = 0; i6 <= 2; i6++) {
								//							for (int i6 = 1; i6 <= 2; i6++) {
								prm_c.vertexPenalty = -0.3 * (double)std::pow(2.0, i6);
								for (int i7 = 1; i7 <= 2; i7++) {
									prm_c.edgePenalty = -0.3 * (double)i7;
									for (int i8 = 0; i8 <= 1; i8++) {
										prm_c.existingVertexGain = 10000 * std::pow(2.0, (double)i8);

										vprm.push_back(prm_c);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	int num_prm=vprm.size();
	std::vector<int> v1=kb::getRandomNumbers(num_prm);
	int num_x = num_prm;
	int num_max = m_num_max_find_circle;

	cv::Ptr<cv::FeatureDetector> blobDetector = cv::SimpleBlobDetector::create(m_prm_blob);

	if (num_x > num_max) { num_x = num_max; }
	for (int k = 0; k < num_x; k++) {
		std::cout << k << "/" << num_prm<< " " << v1[k] << std::endl;

		std::vector<cv::Point2f> vec_p2d;
		prm_c = vprm[v1[k]];
		bool rtn1 = false;
		try {
			rtn1 = cv::findCirclesGrid(
				matFg, m_patternSize, vec_p2d,
				cv::CALIB_CB_SYMMETRIC_GRID,
				blobDetector, prm_c);
		}
		catch (const cv::Exception& e) {
			rtn1 = false;
		}
		if (rtn1 == true) {
			
			std::cout << "minDensity " << prm_c.minDensity << std::endl;
			std::cout << "densityNeighborhoodSize " << prm_c.densityNeighborhoodSize << std::endl;
			std::cout << "minDistanceToAddKeypoint " << prm_c.minDistanceToAddKeypoint << std::endl;
			std::cout << "minGraphConfidence " << prm_c.minGraphConfidence << std::endl;
			std::cout << "convexHullFactor " << prm_c.convexHullFactor << std::endl;
			std::cout << "keypointScale " << prm_c.keypointScale << std::endl;
			std::cout << "vertexPenalty " << prm_c.vertexPenalty << std::endl;
			std::cout << "edgePenalty " << prm_c.edgePenalty << std::endl;
			std::cout << "existingVertexGain " << prm_c.existingVertexGain << std::endl;


			v2d_out = vec_p2d;

			cv::Mat mat1;
			matFg.copyTo(mat1);
			cv::drawChessboardCorners(mat1, m_patternSize, vec_p2d, rtn1);
			cv::imwrite("debug_findCircle.png", mat1);

			if (m_debug > 0) {

				cv::namedWindow("corners", cv::WINDOW_NORMAL);
				cv::imshow("corners", mat1);
				cv::waitKeyEx(0);
			}
			return 1;
		}
	}

	return -1;
}

//	画像読み込み、
int kb::Calib::create(std::string& dname_image, std::string& key)
{
	//	画像パス名リストの読み込み
	std::vector< std::string > filenames;
	if (kb::search_files(dname_image, key.c_str(), filenames) < 0)
		return -1;

	int num_files = filenames.size();
	std::cout << "num of files: " << num_files << std::endl;

	m_vmat1.resize(num_files);
	m_vmat2.resize(num_files);
	m_vflag2.resize(num_files, 0);

	for (int k = 0; k < num_files; k++) {
		std::string path1 = dname_image + filenames[k];
		m_vmat1[k] = cv::imread(path1);

		cv::Size sz = m_vmat1[k].size();
		if (k == 0) {
			int height = sz.height * m_pre_width / sz.width;

			m_szImage1 = sz;
			m_szImage2 = cv::Size(m_pre_width, height);
			m_szImage3 = cv::Size(m_szImage2.width * m_ratio_pre_width, m_szImage2.height * m_ratio_pre_width);

			std::cout << "" << m_szImage1 << std::endl;
			std::cout << "" << m_szImage2 << std::endl;
			std::cout << "" << m_szImage3 << std::endl;
		}
		else {
			if (sz == m_szImage1) {
			}
			else {
				std::cout << "" << sz << std::endl;
			}
		}
		cv::resize(m_vmat1[k], m_vmat2[k], m_szImage2);

		cv::Mat matF;
		if (m_mode_sm > 0) {
			cv::GaussianBlur(m_vmat2[k], matF, cv::Size(5, 5), 2.0);
		}
		else {
			matF = m_vmat2[k];
		}


		std::vector<cv::Point2f> vec_p2d;

		int rtn1 = 0;

		if (rtn1 != 1) {
			cv::Mat mat1;
			matF.copyTo(mat1);

			std::vector<cv::Point2f> temp_vec_p2d;
			rtn1 = findCirclesGrid(mat1, temp_vec_p2d);

			if (rtn1 == 1) {
				vec_p2d = temp_vec_p2d;
				m_vv_p2d.push_back(vec_p2d);
				m_v_idx.push_back(k);
				m_vflag2[k] = 1;
			}
		}

		if (rtn1 != 1) {
			std::cout << "rotate" << std::endl;
			cv::Mat mat1;
			cv::rotate(matF, mat1, 0);
			std::vector<cv::Point2f> temp_vec_p2d;
			rtn1 = findCirclesGrid(mat1, temp_vec_p2d);

			if (rtn1 == 1) {
				vec_p2d = temp_vec_p2d;

				for (int j = 0; j < m_patternSize.height; j++) {
					for (int i = 0; i < m_patternSize.width; i++) {
						vec_p2d[i + j * m_patternSize.width].x = temp_vec_p2d[i + j * m_patternSize.width].y;
						vec_p2d[i + j * m_patternSize.width].y = m_szImage2.height - 1 - temp_vec_p2d[i + j * m_patternSize.width].x;
					}
				}

				m_vv_p2d.push_back(vec_p2d);
				m_v_idx.push_back(k);
				m_vflag2[k] = 1;

			}
		}

		if (rtn1 != 1) {
			for (int kk = 1; kk < 5; kk++) {
				cv::Mat mat1;
				matF.copyTo(mat1);
				double rx = 1.0;
				double ry = 1.0;

				if (kk == 1) {
					cv::resize(matF, mat1, cv::Size(m_szImage2.width * 2, m_szImage2.height), cv::INTER_CUBIC);
					rx = 0.5;
				}
				else if (kk == 2) {
					cv::resize(matF, mat1, cv::Size(m_szImage2.width, m_szImage2.height * 2), cv::INTER_CUBIC);
					ry = 0.5;
				}
				else if (kk == 3) {
					cv::resize(matF, mat1, cv::Size(m_szImage2.width * 2, m_szImage2.height / 2), cv::INTER_CUBIC);
					rx = 0.5;
					ry = 2.0;
				}
				else if (kk == 4) {
					cv::resize(matF, mat1, cv::Size(m_szImage2.width / 2, m_szImage2.height * 2), cv::INTER_CUBIC);
					rx = 2.0;
					ry = 0.5;
				}
				std::vector<cv::Point2f> temp_vec_p2d;

				std::cout << 1.0 / rx << " " << 1.0 / ry << std::endl;
				rtn1 = findCirclesGrid(mat1, temp_vec_p2d);

				if (rtn1 == 1) {
					vec_p2d = temp_vec_p2d;

					for (int j = 0; j < m_patternSize.height; j++) {
						for (int i = 0; i < m_patternSize.width; i++) {
							vec_p2d[i + j * m_patternSize.width].x = temp_vec_p2d[i + j * m_patternSize.width].x * rx;
							vec_p2d[i + j * m_patternSize.width].y = temp_vec_p2d[i + j * m_patternSize.width].y * ry;
						}
					}

					m_vv_p2d.push_back(vec_p2d);
					m_v_idx.push_back(k);
					m_vflag2[k] = 1;

					break;
				}
			}
		}
	}

	return 0;
}

//	画像読み込み、
int kb::Calib::findCircles(std::string& path_image)
{
	m_vmat1.resize(1);
	m_vmat2.resize(1);
	m_vflag2.resize(1, 0);

	{
		m_vmat1[0] = cv::imread(path_image);

		cv::Size sz = m_vmat1[0].size();
		{
			int height = sz.height * m_pre_width / sz.width;

			m_szImage1 = sz;
			m_szImage2 = cv::Size(m_pre_width, height);
			m_szImage3 = cv::Size(m_szImage2.width * m_ratio_pre_width, m_szImage2.height * m_ratio_pre_width);

			std::cout << "" << m_szImage1 << std::endl;
			std::cout << "" << m_szImage2 << std::endl;
			std::cout << "" << m_szImage3 << std::endl;
		}
		cv::resize(m_vmat1[0], m_vmat2[0], m_szImage2);

		cv::Mat matF;
		if (m_mode_sm > 0) {
			cv::GaussianBlur(m_vmat2[0], matF, cv::Size(5, 5), 2.0);
		}
		else {
			matF = m_vmat2[0];
		}


		std::vector<cv::Point2f> vec_p2d;

		int rtn1 = 0;

		for (int kk = 0; kk < 5; kk++) {
			cv::Mat mat1;
			matF.copyTo(mat1);
			double rx = 1.0;
			double ry = 1.0;

			if (kk == 1) {
				cv::resize(matF, mat1, cv::Size(m_szImage2.width * 2, m_szImage2.height), cv::INTER_CUBIC);
				rx = 0.5;
			}
			else if (kk == 2) {
				cv::resize(matF, mat1, cv::Size(m_szImage2.width, m_szImage2.height * 2), cv::INTER_CUBIC);
				ry = 0.5;
			}
			else if (kk == 3) {
				cv::resize(matF, mat1, cv::Size(m_szImage2.width * 2, m_szImage2.height / 2), cv::INTER_CUBIC);
				rx = 0.5;
				ry = 2.0;
			}
			else if (kk == 4) {
				cv::resize(matF, mat1, cv::Size(m_szImage2.width / 2, m_szImage2.height * 2), cv::INTER_CUBIC);
				rx = 2.0;
				ry = 0.5;
			}
			std::vector<cv::Point2f> temp_vec_p2d;

			std::cout << 1.0 / rx << " " << 1.0 / ry << std::endl;
			rtn1 = findCirclesGrid(mat1, temp_vec_p2d);

			if (rtn1 == 1) {
				vec_p2d = temp_vec_p2d;

				for (int j = 0; j < m_patternSize.height; j++) {
					for (int i = 0; i < m_patternSize.width; i++) {
						vec_p2d[i + j * m_patternSize.width].x = temp_vec_p2d[i + j * m_patternSize.width].x * rx;
						vec_p2d[i + j * m_patternSize.width].y = temp_vec_p2d[i + j * m_patternSize.width].y * ry;
					}
				}

				m_vv_p2d.push_back(vec_p2d);
				m_v_idx.push_back(0);
				m_vflag2[0] = 1;

				break;
			}
		}

	}

	return 0;
}


//
int kb::Calib::create2nd(kb::Calib& calib2)
{
	int num_vmat2 = m_vmat2.size();
	for (int k = 0; k < num_vmat2; k++) {
		//std::cout << k << std::endl;
		if (m_vflag2[k] > 0)
			continue;

		cv::Mat mat2;
		calib2.undistort(m_vmat2[k], mat2);
		std::cout << mat2.size() << std::endl;


		cv::Mat mat2x=mat2;
		//cv::resize(mat2, mat2x, m_szImage2);

		//cv::Mat matF;
		//cv::GaussianBlur(mat2x, matF, cv::Size(5, 5), 2.0);

		cv::namedWindow("corners", cv::WINDOW_NORMAL);
		cv::imshow("corners", mat2);
		cv::waitKeyEx(0);

		cv::Mat matF = mat2x;
		std::vector<cv::Point2f> vec_p2d;
		findCirclesGrid(matF, vec_p2d);
	}
	return 0;
}

//
int kb::Calib::calibrate()
{
	int num_vv = m_vv_p2d.size();
	int num_ps = m_patternSize.width * m_patternSize.height;

	std::vector<std::vector<cv::Point3f>>	vv_p3d(num_vv);
	for (int i = 0; i < num_vv; i++) {
		for (int j = 0; j < num_ps; j++) {
			vv_p3d[i].push_back(
				cv::Point3f(
					static_cast<float>(j % m_patternSize.width)* m_step_width,
					static_cast<float>(j / m_patternSize.width)* m_step_width,
					0.0)
			);
		}
	}


	int flag1 = cv::CALIB_FIX_K3 |  cv::CALIB_FIX_PRINCIPAL_POINT;
	//int flag1 = cv::CALIB_FIX_K3 | cv::CALIB_ZERO_TANGENT_DIST;// 0;// cv::CALIB_FIX_PRINCIPAL_POINT;
	//int flag1 = cv::CALIB_FIX_K1 | cv::CALIB_FIX_K2 | cv::CALIB_FIX_K3;// 0;// cv::CALIB_FIX_PRINCIPAL_POINT;
	//int flag1 = cv::CALIB_FIX_PRINCIPAL_POINT | cv::CALIB_RATIONAL_MODEL;
	// cv::fisheye::CALIB_FIX_SKEW | cv::fisheye::CALIB_CHECK_COND;
	cv::TermCriteria	criteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, m_num_iter, m_eps);
	std::cout << "iter num=" << m_num_iter<<", eps="<< m_eps << std::endl;

	m_distCoef = cv::Mat(1, 4, CV_64FC1, cv::Scalar(0.0));

	cv::calibrateCamera(
		vv_p3d, m_vv_p2d, m_szImage2,
		m_camIn, m_distCoef,
		m_vecR, m_vecT,
		flag1, criteria);

	//	remap用の処理パラメータの計算
	m_camIn2 = cv::getOptimalNewCameraMatrix(m_camIn, m_distCoef, m_szImage2, m_alpha, m_szImage3);
	cv::initUndistortRectifyMap(m_camIn, m_distCoef, cv::Mat(), m_camIn2, m_szImage3, CV_32FC1, m_map1, m_map2);

	std::cout << m_distCoef << std::endl;

	return 0;
}

int kb::Calib::calibrateFisheye()
{
	int num_vv = m_vv_p2d.size();
	int num_ps = m_patternSize.width * m_patternSize.height;

	std::vector<std::vector<cv::Point3f>>	vv_p3d(num_vv);
	for (int i = 0; i < num_vv; i++) {
		for (int j = 0; j < num_ps; j++) {
			vv_p3d[i].push_back(
				cv::Point3f(
					static_cast<float>(j % m_patternSize.width)* m_step_width,
					static_cast<float>(j / m_patternSize.width)* m_step_width,
					0.0)
			);
		}
	}

	//int flag1 = cv::fisheye::CALIB_FIX_SKEW;// | cv::fisheye::CALIB_CHECK_COND;
	int flag1 = cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC | 
		cv::fisheye::CALIB_CHECK_COND |
		cv::fisheye::CALIB_FIX_SKEW;

	cv::TermCriteria	criteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, m_num_iter, m_eps);
	//m_distCoef = cv::Mat(1, 4, CV_64FC1, cv::Scalar(0.0));

	//std::cout << "cv::fisheye::calibrate" << std::endl;
	cv::fisheye::calibrate(
		vv_p3d, m_vv_p2d, m_szImage2,
		m_camIn, m_distCoef,
		m_vecR, m_vecT,
		flag1);// , criteria);
	std::cout << m_camIn << std::endl;
	std::cout << m_distCoef << std::endl;

	//	remap用の処理パラメータの計算
	//std::cout << "cv::fisheye::estimateNewCameraMatrixForUndistortRectify" << std::endl;
	cv::fisheye::estimateNewCameraMatrixForUndistortRectify(m_camIn, m_distCoef, m_szImage2, cv::Matx33d::eye(), m_camIn2, 1);
	cv::fisheye::initUndistortRectifyMap(m_camIn, m_distCoef, cv::Matx33d::eye(), m_camIn2, m_szImage3, CV_32FC1, m_map1, m_map2);

	std::cout << m_camIn2 << std::endl;

	return 0;
}

int kb::Calib::debug_undistort()
{
	int num_vmat2 = m_vmat2.size();
	for (int k = 0; k < num_vmat2; k++) {
		cv::Mat mat1;
		undistort(m_vmat2[k], mat1);

		std::cout << mat1.size() << std::endl;

		cv::Mat mat2;
		m_vmat2[k].copyTo(mat2);
		{
			int k2 = -1;
			int num_idx = m_v_idx.size();
			for (int i = 0; i < num_idx; i++) {
				if (m_v_idx[i] == k) {
					k2 = i;
					break;
				}
			}

			//int num_vv2 = m_vv_p2d.size();
			if (k2 >= 0) {
				int num_p2d = m_vv_p2d[k2].size();
				for (int i = 0; i < num_p2d; i++) {
					cv::circle(mat2, m_vv_p2d[k2][i], 6, cv::Scalar(0, 255, 0), 3);
				}

				//	原画像上の座標からゆがみ補正した座標へ変換
				std::vector<cv::Point2f> v2d;
				cv::undistortPoints(m_vv_p2d[k2], v2d, m_camIn, m_distCoef);

				int num2 = v2d.size();
				//std::cout << num2 << std::endl;
				for (int i = 0; i < num2; i++) {
					//	原画像上の座標からゆがみ補正した座標へ変換
					//std::cout << v2d[i] << std::endl;
					double x = m_camIn2.at<double>(0, 0) * v2d[i].x + m_camIn2.at<double>(0, 1) * v2d[i].y + m_camIn2.at<double>(0, 2);
					double y = m_camIn2.at<double>(1, 0) * v2d[i].x + m_camIn2.at<double>(1, 1) * v2d[i].y + m_camIn2.at<double>(1, 2);
					cv::circle(mat1, cv::Point(x, y), 6, cv::Scalar(255, 255, 0), 3);

					//	ゆがみ補正した画像から、元の位置を取得
					double x2 = m_map1.at<float>(y, x);
					double y2 = m_map2.at<float>(y, x);
					//std::cout << x2<<" "<<y2 << std::endl;

					cv::circle(mat2, cv::Point(x2,y2), 3, cv::Scalar(0, 255, 255), 3);
				}
			}
		}

		cv::namedWindow("corners", cv::WINDOW_NORMAL);
		cv::imshow("corners", mat2);
		cv::namedWindow("undistort", cv::WINDOW_NORMAL);
		cv::imshow("undistort", mat1);
		cv::waitKeyEx(0);

	}
	return 0;
}


//	歪み補正の実行
int kb::Calib::undistort(cv::Mat& mat1, cv::Mat& mat_out)
{
	cv::Size sz1 = mat1.size();

	cv::Mat mat1pre;
	if (sz1 != m_szImage2) {
		cv::resize(mat1, mat1pre, m_szImage2);
	}
	else {
		mat1pre = mat1;
	}

	cv::remap(mat1pre, mat_out, m_map1, m_map2, cv::INTER_LINEAR);

	return 0;
}


int kb::Calib::load_param(std::string& path_prm)
{
	kb::read(path_prm.c_str(), "chessboard", "debug", m_debug);
	
	int cx = m_patternSize.width;
	int cy = m_patternSize.height;
	kb::read(path_prm.c_str(), "chessboard", "nx", cx);
	kb::read(path_prm.c_str(), "chessboard", "ny", cy);
	m_patternSize = cv::Size(cx, cy);

	kb::read(path_prm.c_str(), "chessboard", "mode_sm", m_mode_sm);

	kb::read(path_prm.c_str(), "chessboard", "step_width", m_step_width);
	kb::read(path_prm.c_str(), "chessboard", "pre_width", m_pre_width);
	kb::read(path_prm.c_str(), "chessboard", "ratio_pre_width", m_ratio_pre_width);

	kb::read(path_prm.c_str(), "chessboard", "num_iter", m_num_iter);
	kb::read(path_prm.c_str(), "chessboard", "eps", m_eps);

	kb::read(path_prm.c_str(), "chessboard", "num_max_find_circle", m_num_max_find_circle);
	
	kb::read(path_prm.c_str(), "chessboard", "alpha", m_alpha);
	std::cout << "m_alpha= "<< m_alpha << std::endl;
	

	//kb::read(path_prm.c_str(), "getOptimalNewCameraMatrix", "alpha", m_alpha);

	kb::read(path_prm, m_prm_c);
	kb::read(path_prm, m_prm_blob);

	return 0;
}

int kb::Calib::save(std::string& path)
{
	cv::FileStorage file;
	file.open(path, cv::FileStorage::Mode::WRITE);

	cv::write(file, "intrinsic matrix", m_camIn);
	cv::write(file, "distortion matrix", m_distCoef);
	cv::write(file, "intrinsic matrix2", m_camIn2);
	cv::write(file, "input-image", m_szImage1);
	cv::write(file, "pre-image", m_szImage2);
	cv::write(file, "undistort-image", m_szImage3);

	return 0;
}

int kb::Calib::load(std::string& path)
{
	cv::FileStorage file;
	file.open(path, cv::FileStorage::Mode::READ);
	if (file.isOpened() == false)
		return -1;

	file["intrinsic matrix"] >> m_camIn;
	file["distortion matrix"] >> m_distCoef;
	//file["intrinsic matrix2"] >> m_camIn2;
	//cv::read(file["intrinsic matrix"], m_camIn);
	//cv::read(file["distortion matrix"], m_distCoef);
	std::cout << m_camIn << std::endl;
	std::cout << m_distCoef << std::endl;
	//std::cout << m_camIn2 << std::endl;

	std::vector<int> sz1;	file["input-image"] >> sz1;
	std::vector<int> sz2;	file["pre-image"] >> sz2;
	std::vector<int> sz3;	file["undistort-image"] >> sz3;
	if (sz1.size() >= 2) {
		m_szImage1.width = sz1[0];
		m_szImage1.height = sz1[1];
	}
	if (sz2.size() >= 2) {
		m_szImage2.width = sz2[0];
		m_szImage2.height = sz2[1];
	}
	if (sz3.size() >= 2) {
		m_szImage3.width = sz3[0];
		m_szImage3.height = sz3[1];
	}

	std::cout << m_szImage1 << std::endl;
	std::cout << m_szImage2 << std::endl;
	std::cout << m_szImage3 << std::endl;

	//cv::read(node["input-image"], m_szImage1);
	//cv::read(node["pre-image"], m_szImage2);
	//cv::read(node["undistort-image"], m_szImage3);

	//	remap用の処理パラメータの計算
	m_camIn2 = cv::getOptimalNewCameraMatrix(m_camIn, m_distCoef, m_szImage2, m_alpha, m_szImage3);
	cv::initUndistortRectifyMap(m_camIn, m_distCoef, cv::Mat(), m_camIn2, m_szImage3, CV_32FC1, m_map1, m_map2);

	return 0;
}

int kb::Calib::load_test(std::string& path)
{
	cv::FileStorage file;
	file.open(path, cv::FileStorage::Mode::READ);
	if (file.isOpened() == false)
		return -1;

	file["intrinsic matrix"] >> m_camIn;
	file["distortion matrix"] >> m_distCoef;
	//file["intrinsic matrix2"] >> m_camIn2;
	//cv::read(file["intrinsic matrix"], m_camIn);
	//cv::read(file["distortion matrix"], m_distCoef);

	m_distCoef.at<double>(1)=-m_distCoef.at<double>(0)* m_distCoef.at<double>(0);

	std::cout << m_camIn << std::endl;
	std::cout << m_distCoef << std::endl;
	//std::cout << m_camIn2 << std::endl;

	std::vector<int> sz1;	file["input-image"] >> sz1;
	std::vector<int> sz2;	file["pre-image"] >> sz2;
	std::vector<int> sz3;	file["undistort-image"] >> sz3;
	if (sz1.size() >= 2) {
		m_szImage1.width = sz1[0];
		m_szImage1.height = sz1[1];
	}
	if (sz2.size() >= 2) {
		m_szImage2.width = sz2[0];
		m_szImage2.height = sz2[1];
	}
	if (sz3.size() >= 2) {
		m_szImage3.width = sz3[0];
		m_szImage3.height = sz3[1];
	}

	std::cout << m_szImage1 << std::endl;
	std::cout << m_szImage2 << std::endl;
	std::cout << m_szImage3 << std::endl;

	//cv::read(node["input-image"], m_szImage1);
	//cv::read(node["pre-image"], m_szImage2);
	//cv::read(node["undistort-image"], m_szImage3);

	//	remap用の処理パラメータの計算
	m_camIn2 = cv::getOptimalNewCameraMatrix(m_camIn, m_distCoef, m_szImage2, m_alpha, m_szImage3);
	cv::initUndistortRectifyMap(m_camIn, m_distCoef, cv::Mat(), m_camIn2, m_szImage3, CV_32FC1, m_map1, m_map2);

	return 0;
}


/*
int kb::calib_fisheye(int argc, char* argv[])
{
	//-----------------------------
	//	
	std::string dirname = argv[2];
	std::string key = argv[3];
	std::string path_prm = argv[4];
	std::string dirname_out = argv[5];

	std::string dirname_test = argv[6];

	//std::string path_out1 = argv[5];// dirname_out + "cam_in.txt";
	std::string path_out1 = dirname_out + "cam_in.txt";


	kb::Calib calib;
	calib.load_param(path_prm);
	calib.create(dirname, key);
	//calib.create2nd(calib2);

	calib.calibrate();
	//calib.calibrateFisheye();
	//calib.debug_undistort();

	calib.save(path_out1);

	//
	std::vector< std::string > fname_test;
	kb::search_files(dirname_test, key.c_str(), fname_test);
	int num_test = fname_test.size();
	{
		for (int k = 0; k < num_test; k++) {
			std::string path2 = dirname_test + fname_test[k];
			cv::Mat mat2a = cv::imread(path2);

			cv::Mat mat2b;
			calib.undistort(mat2a, mat2b);

			cv::namedWindow("corners", cv::WINDOW_NORMAL);
			cv::imshow("corners", mat2a);
			cv::namedWindow("undistort", cv::WINDOW_NORMAL);
			cv::imshow("undistort", mat2b);
			cv::waitKeyEx(0);

			std::string path2_out = dirname_out + fname_test[k];
			cv::imwrite(path2_out, mat2b);
		}
	}

	return 0;
}
*/

int kb::calib_fisheye(int argc, char* argv[])
{
	//-----------------------------
	//	
	std::string dirname = argv[2];
	std::string key = argv[3];
	std::string path_prm = argv[4];
	std::string path_camin = argv[5];// dirname_out + "cam_in.txt";


	kb::Calib calib;
	calib.load_param(path_prm);
	std::cout << "check1" << std::endl;
	calib.create(dirname, key);
	calib.calibrate();
	calib.save(path_camin);




	return 0;
}


int kb::undistort_fisheye(int argc, char* argv[])
{
	//-----------------------------
	//	
	std::string dirname = argv[2];
	std::string key = argv[3];
	std::string path_prm = argv[4];
	std::string path_cam_in = argv[5];
	std::string dirname_out = argv[6];


	//kb::Calib calib2;
	//calib2.load_param(path_prm);
	//calib2.load(path_out1);

	kb::Calib calib;
	calib.load_param(path_prm);
	calib.load(path_cam_in);


	//
	std::vector< std::string > fname_test;
	kb::search_files(dirname, key.c_str(), fname_test);
	int num_test = fname_test.size();
	{
		for (int k = 0; k < num_test; k++) {
			std::string path2 = dirname + fname_test[k];
			cv::Mat mat2a = cv::imread(path2);

			cv::Mat mat2b;
			calib.undistort(mat2a, mat2b);

			std::string path2_out = dirname_out + fname_test[k];
			cv::imwrite(path2_out, mat2b);

			//cv::namedWindow("corners", cv::WINDOW_NORMAL);
			//cv::imshow("corners", mat2a);
			//cv::namedWindow("undistort", cv::WINDOW_NORMAL);
			//cv::imshow("undistort", mat2b);
			//cv::waitKeyEx(0);
		}
	}

	return 0;
}

int kb::undistort_fisheye2(int argc, char* argv[])
{
	//-----------------------------
	//	
	std::string path_in = argv[2];
	std::string path_prm = argv[3];
	std::string path_cam_in = argv[4];
	std::string path_out = argv[5];

	kb::Calib calib;
	calib.load_param(path_prm);
	calib.load(path_cam_in);
	std::cout << path_prm << std::endl;
	std::cout << "m_alpha = " << calib.m_alpha << std::endl;
	//cv::waitKeyEx(5000);
	//
	cv::Mat mat2a = cv::imread(path_in);

	cv::Mat mat2b;
	calib.undistort(mat2a, mat2b);

	cv::imwrite(path_out, mat2b);


	return 0;
}

/*
bool kb::findCirclesGrid(
	cv::Mat& matF_in,
	cv::Size patternSize,
	std::vector<cv::Point2f>& vec_p2d_out
)
{
	double vr[10][2] = {
		1.0, 1.0,
		2.0, 2.0,
		4.0, 4.0,
		0.5, 1.0,
		1.0, 0.5,

		0.5, 1.0,
		0.5, 0.5,
		0.5, 0.25,
		0.25, 0.5,
		0.25, 0.25
	};

	bool rtn1 = false;
	for (int k = 0; k < 7; k++) {
		cv::Size sz = matF_in.size();

		std::vector<cv::Point2f> vec_p2d;
		cv::Mat matF, mat1;
		matF_in.copyTo(matF);
		double rx = 1.0;
		double ry = 1.0;

		int k2 = k;
		matF.copyTo(mat1);
		if (k2 == 1) {
			cv::resize(matF, mat1, cv::Size(sz.width * 2, sz.height), cv::INTER_CUBIC);
			rx = 0.5;
		}
		else if (k2 == 2) {
			cv::resize(matF, mat1, cv::Size(sz.width * 2, sz.height * 2), cv::INTER_CUBIC);
			rx = 0.5;
			ry = 0.5;
		}
		else if (k2 == 3) {
			cv::resize(matF, mat1, cv::Size(sz.width, sz.height * 2), cv::INTER_CUBIC);
			ry = 0.5;
		}
		else if (k2 == 4) {
			cv::resize(matF, mat1, cv::Size(sz.width * 4, sz.height * 2), cv::INTER_CUBIC);
			rx = 0.25;
			rx = 0.5;
		}
		else if (k2 == 5) {
			cv::resize(matF, mat1, cv::Size(sz.width * 4, sz.height * 4), cv::INTER_CUBIC);
			rx = 0.25;
			ry = 0.25;
		}
		else if (k2 == 6) {
			cv::resize(matF, mat1, cv::Size(sz.width * 2, sz.height * 4), 0, 0, cv::INTER_CUBIC);
			rx = 0.5;
			ry = 0.25;
		}

		std::cout << rx << " " << ry << std::endl;
		rtn1 = cv::findCirclesGrid(mat1, patternSize, vec_p2d, cv::CALIB_CB_SYMMETRIC_GRID);

		if (rtn1 == true) {
			cv::Mat matD;
			mat1.copyTo(matD);

			std::cout << "success findCirclesGrid: " << k << std::endl;

			vec_p2d_out = vec_p2d;
			if (k > 0) {
				for (int j = 0; j < patternSize.height; j++) {
					for (int i = 0; i < patternSize.width; i++) {
						vec_p2d_out[i + j * patternSize.width].x = vec_p2d[i + j * patternSize.width].x * rx;
						vec_p2d_out[i + j * patternSize.width].y = vec_p2d[i + j * patternSize.width].y * ry;
					}
				}
			}

			return rtn1;
		}
	}
	return rtn1;
}
*/

int kb::findCirclesGrid(
	cv::Mat& matF_in,
	cv::Size patternSize,
	std::vector<cv::Point2f>& vec_p2d_out
)
{
	double vr[9][2] = {
		1.0, 1.0,
		0.5, 0.5, 
		0.25, 0.25, 
		1.0, 2.0,
		2.0, 1.0,

		2.0, 2.0,
		2.0, 4.0,
		4.0, 2.0,
		4.0, 4.0
	};

	for (int k = 0; k < 9; k++) {
		int rtn1 = kb::findCirclesGrid(matF_in, patternSize, vec_p2d_out, vr[k][0], vr[k][1]);
		if (rtn1 >= 0)
			return rtn1;
	}
	return -1;
}


int kb::findCirclesGrid(
	cv::Mat& matF_in,
	cv::Size szPtn,
	std::vector<cv::Point2f>& vec_p2d_out,
	double ratio_x, double ratio_y
)
{
	cv::Size sz = matF_in.size();

	double rx = 1.0 / ratio_x;
	double ry = 1.0 / ratio_y;

	cv::Mat matF;
	cv::resize(matF_in, matF, cv::Size(sz.width * ratio_x, sz.height*ratio_y), cv::INTER_CUBIC);

	bool rtn1 = false;
	std::cout << rx << " " << ry << std::endl;
	std::vector<cv::Point2f> vec_p2d;
	try {
		rtn1 = cv::findCirclesGrid(matF, szPtn, vec_p2d, cv::CALIB_CB_SYMMETRIC_GRID);
	}catch (const cv::Exception& e) {
		rtn1 = false;
	}

	if (rtn1 == true) {

		std::cout << "success findCirclesGrid: " << rx << " " << ry << std::endl;

		vec_p2d_out = vec_p2d;
		for (int j = 0; j < szPtn.height; j++) {
			for (int i = 0; i < szPtn.width; i++) {
				vec_p2d_out[i + j * szPtn.width].x = vec_p2d[i + j * szPtn.width].x * rx;
				vec_p2d_out[i + j * szPtn.width].y = vec_p2d[i + j * szPtn.width].y * ry;
			}
		}
		return 1;
	}

	cv::Size szPtn2(szPtn.height, szPtn.width);
	vec_p2d.clear();
	try {
		rtn1 = cv::findCirclesGrid(matF, szPtn2, vec_p2d, cv::CALIB_CB_SYMMETRIC_GRID);
	}
	catch (const cv::Exception& e) {
		rtn1 = false;
	}
	if (rtn1 == true) {

		std::cout << "success findCirclesGrid: " << rx << " " << ry << std::endl;

		vec_p2d_out = vec_p2d;
		for (int j = 0; j < szPtn.height; j++) {
			for (int i = 0; i < szPtn.width; i++) {
				vec_p2d_out[i + j * szPtn.width].x = vec_p2d[i * szPtn.height + szPtn.height - 1 - j].x * rx;
				vec_p2d_out[i + j * szPtn.width].y = vec_p2d[i * szPtn.height + szPtn.height - 1 - j].y * ry;
			}
		}
		return 2;
	}

	return -1;
}


#if 0
bool kb::findCirclesGrid(
	cv::Mat& matF,
	cv::Size patternSize,
	std::vector<cv::Point2f>& vec_p2d_out
)
{
	bool rtn1 = false;
	for (int k = 0; k < 8; k++) {
		cv::Size sz = matF.size();

		std::vector<cv::Point2f> vec_p2d;
		cv::Mat mat1;
		matF.copyTo(mat1);
		double rx = 1.0;
		double ry = 1.0;

		int k2 = k;
		if (k > 7) {
			int k2 = k % 7;
			cv::rotate(matF, mat1, 0);

		}
		if (k == 1) {
			cv::rotate(matF, mat1, 0);
			{
				cv::Mat matF2g, matFg;
				cv::cvtColor(matF, matFg, cv::COLOR_BGR2GRAY);
				cv::threshold(matFg, matF2g, 127, 255, cv::THRESH_OTSU);
				cv::cvtColor(matF2g, mat1, cv::COLOR_GRAY2BGR);
			}
		}
		else if (k == 2) {
			cv::resize(matF, mat1, cv::Size(sz.width * 2, sz.height), cv::INTER_CUBIC);
			rx = 0.5;
		}
		else if (k == 3) {
			cv::resize(matF, mat1, cv::Size(sz.width * 2, sz.height * 2), cv::INTER_CUBIC);
			rx = 0.5;
			ry = 0.5;
		}
		else if (k == 4) {
			cv::resize(matF, mat1, cv::Size(sz.width, sz.height * 2), cv::INTER_CUBIC);
			ry = 0.5;
		}
		else if (k == 5) {
			cv::resize(matF, mat1, cv::Size(sz.width * 4, sz.height * 2), cv::INTER_CUBIC);
			rx = 0.25;
			rx = 0.5;
		}
		else if (k == 6) {
			cv::resize(matF, mat1, cv::Size(sz.width * 4, sz.height * 4), cv::INTER_CUBIC);
			rx = 0.25;
			ry = 0.25;
		}
		else if (k == 7) {
			cv::resize(matF, mat1, cv::Size(sz.width * 2, sz.height * 4), 0, 0, cv::INTER_CUBIC);
			rx = 0.5;
			ry = 0.25;
		}

		rtn1 = cv::findCirclesGrid(mat1, patternSize, vec_p2d, cv::CALIB_CB_SYMMETRIC_GRID);

		if (rtn1 == true) {
			cv::Mat matD;
			mat1.copyTo(matD);
			//cv::drawChessboardCorners(matD, patternSize, vec_p2d, rtn1);

			//cv::namedWindow("corners", cv::WINDOW_NORMAL);
			//cv::imshow("corners", matD);
			//cv::waitKeyEx(0);

			std::cout << "success findCirclesGrid: " << k << std::endl;

			vec_p2d_out = vec_p2d;
			if (k > 0) {
				for (int j = 0; j < patternSize.height; j++) {
					for (int i = 0; i < patternSize.width; i++) {
						vec_p2d_out[i + j * patternSize.width].x = vec_p2d[i + j * patternSize.width].x * rx;
						vec_p2d_out[i + j * patternSize.width].y = vec_p2d[i + j * patternSize.width].y * ry;
					}
				}
			}

			return rtn1;
		}
	}
	return rtn1;
}
#endif

int kb::findCirclesGrid2(cv::Mat& matF,
	cv::Size patternSize,
	std::vector<cv::Point2f>& vec_p2d_out
)
{
	cv::Size sz=matF.size();

	int rtn1 = kb::findCirclesGrid(matF, patternSize,  vec_p2d_out);
	if (rtn1>=0)
		return rtn1;
	//{
	//	cv::Mat mat1;
	//	cv::rotate(matF, mat1, 0);

	//	std::vector<cv::Point2f> vec_p2d_2;
	//	rtn1 = kb::findCirclesGrid(mat1, patternSize, vec_p2d_2);
	//	if (rtn1 == true)
	//	{
	//		vec_p2d_out = vec_p2d_2;
	//		int num = vec_p2d_2.size();
	//		for (int j = 0; j < patternSize.height; j++) {
	//			for (int i = 0; i < patternSize.width; i++) {
	//				vec_p2d_out[i + j * patternSize.width].x = vec_p2d_2[i + j * patternSize.width].y;
	//				vec_p2d_out[i + j * patternSize.width].y = sz.height-1-vec_p2d_2[i + j * patternSize.width].x;
	//			}
	//		}
	//		return rtn1;
	//	}
	//}


	//cv::Mat matF2;
	//kb::equalizeHistForRGB(matF, matF2, 1.0, 0, 2.0, 1.0);

	//rtn1 = kb::findCirclesGrid(matF2, patternSize,  vec_p2d_out);

	return rtn1;
}

int kb::corner4(
	std::vector<cv::Point2f>& vec_p2d,
	cv::Size patternSize,
	cv::Point2f p_out[4]
)
{
	int cx = patternSize.width;
	int cy = patternSize.height;

	cv::Point2f v1[4] = {
		vec_p2d[0], 
		vec_p2d[cx - 1],
		vec_p2d[cx*cy - 1], 
		vec_p2d[cx*cy - cx] 
	};

	cv::Point2f v0 = (v1[0] + v1[1]+ v1[2] + v1[3]) * 0.25;

	cv::Point2f dv1[4];
	int i0 = 0;
	for (int i = 0; i < 4; i++) {
		dv1[i] = v1[i] - v0;
		if (dv1[i].x < 0.0 && dv1[i].y < 0.0) {
			i0 = i;
		}
	}

	for (int i = 0; i < 4; i++) {
		int i2 = (i + i0) % 4;
		p_out[i] = v1[i2];
	}


	return i0;
}

