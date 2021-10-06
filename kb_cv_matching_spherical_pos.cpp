#define _USE_MATH_DEFINES
#include <math.h>

#include "ceres/ceres.h"
#include "glog/logging.h"

#include "kb_cv_matching_spherical_pos.h"
#include "kb_cv_spherical_mapping.h"




//	球面上でコストを計算
struct Residual3d_sphere {
	Residual3d_sphere(cv::Point3f& p1, cv::Point3f& p2, double angle[3])
	{
		m_p1[0] = p1.x;
		m_p1[1] = p1.y;
		m_p1[2] = p1.z;

		m_p2[0] = p2.x;
		m_p2[1] = p2.y;
		m_p2[2] = p2.z;

		m_angle[0] = angle[0];
		m_angle[1] = angle[1];
		m_angle[2] = angle[2];
	}

	template <typename T>
	bool operator()(const T* const angle2, T* error) const
	{
		Eigen::Matrix<T, 3, 3> matR1;
		matR1 = Eigen::AngleAxis<T>((m_angle[2] / T(180.0)) * T(M_PI), Eigen::Matrix<T, 3, 1>::UnitY())
			* Eigen::AngleAxis<T>((m_angle[1] / T(180.0)) * T(M_PI), Eigen::Matrix<T, 3, 1>::UnitX())
			* Eigen::AngleAxis<T>((m_angle[0] / T(180.0)) * T(M_PI), Eigen::Matrix<T, 3, 1>::UnitZ());
		Eigen::Matrix<T, 3, 3> matR2;
		matR2 = Eigen::AngleAxis<T>((angle2[2] / T(180.0)) * T(M_PI), Eigen::Matrix<T, 3, 1>::UnitY())
			* Eigen::AngleAxis<T>((angle2[1] / T(180.0)) * T(M_PI), Eigen::Matrix<T, 3, 1>::UnitX())
			* Eigen::AngleAxis<T>((angle2[0] / T(180.0)) * T(M_PI), Eigen::Matrix<T, 3, 1>::UnitZ());

		Eigen::Matrix<T, 3, 1> p1;
		p1(0, 0) = T(m_p1[0]);
		p1(1, 0) = T(m_p1[1]);
		p1(2, 0) = T(m_p1[2]);
		Eigen::Matrix<T, 3, 1> p2;
		p2(0, 0) = T(m_p2[0]);
		p2(1, 0) = T(m_p2[1]);
		p2(2, 0) = T(m_p2[2]);

		Eigen::Matrix<T, 3, 1> p1t = matR1 * p1;
		Eigen::Matrix<T, 3, 1> p2t = matR2 * p2;

		//コスト
		error[0] = p2t(0, 0) - p1t(0, 0);
		error[1] = p2t(1, 0) - p1t(1, 0);
		error[2] = p2t(2, 0) - p1t(2, 0);

		return true;
	}
	/*
	template <typename T>
	bool operator()(const T* const angle, T* error) const
	{
		Eigen::Matrix<T, 3, 3> matR;
		matR = Eigen::AngleAxis<T>((angle[2] / T(180.0)) * T(M_PI), Eigen::Matrix<T, 3, 1>::UnitZ())
			* Eigen::AngleAxis<T>((angle[1] / T(180.0)) * T(M_PI), Eigen::Matrix<T, 3, 1>::UnitX())
			*Eigen::AngleAxis<T>((angle[0] / T(180.0)) * T(M_PI), Eigen::Matrix<T, 3, 1>::UnitZ());

		Eigen::Matrix<T, 3, 1> p1;
		p1(0, 0) = T(m_p1[0]);
		p1(1, 0) = T(m_p1[1]);
		p1(2, 0) = T(m_p1[2]);
		Eigen::Matrix<T, 3, 1> p2 = matR * p1;

		//コスト
		error[0] = T(m_p2[0]) - p2(0, 0);
		error[1] = T(m_p2[1]) - p2(1, 0);
		error[2] = T(m_p2[2]) - p2(2, 0);

		return true;
	}
	*/

private:
	double m_p1[3], m_p2[3];
	double m_angle[3];
};



int kb::matching_spherical_pos(
	std::vector<cv::Point3f>& vp1,
	std::vector<cv::Point3f>& vp2,
	double angle[3],
	double matR[9],
	double coef_lossfunc,
	double range_angle[3],
	bool mode_stdout,
	int num_threads,
	int max_num_iterations)
{
	//最適化問題を解く用のオブジェクトの生成
	ceres::Problem problem;
	//外れ値用損失関数
	ceres::LossFunction* loss_function = new ceres::CauchyLoss(coef_lossfunc);

	double angle_ini[3] = { angle[0], angle[1], angle[2] };

	int num_vp = vp1.size();
	for (int i = 0; i < num_vp; i++) {
		problem.AddResidualBlock(
			new ceres::AutoDiffCostFunction<Residual3d_sphere, 3, 3>(
				new Residual3d_sphere(vp1[i], vp2[i], angle_ini)), loss_function, angle);
	}

	problem.SetParameterLowerBound(angle, 0, angle[0] - range_angle[0]);
	problem.SetParameterUpperBound(angle, 0, angle[0] + range_angle[0]);
	problem.SetParameterLowerBound(angle, 1, angle[1] - range_angle[1]);
	problem.SetParameterUpperBound(angle, 1, angle[1] + range_angle[1]);
	problem.SetParameterLowerBound(angle, 2, angle[2] - range_angle[2]);
	problem.SetParameterUpperBound(angle, 2, angle[2] + range_angle[2]);

	//std::cout << "optimization ... " << std::endl;

	ceres::Solver::Options options;

	//CXSparseをインストールしていないときはDENSE_*にしないとエラーになる。
	options.linear_solver_type = ceres::SPARSE_NORMAL_CHOLESKY;
	//options.linear_solver_type = ceres::DENSE_QR;
	//処理途中のログ出力
	options.minimizer_progress_to_stdout = mode_stdout;
	//スレッド数設定
	options.num_threads = num_threads;
	//options.num_linear_solver_threads = num_threads;
	//最適化の最大試行回数を指定
	options.max_num_iterations = max_num_iterations;

	//最適化実行
	ceres::Solver::Summary summary;
	Solve(options, &problem, &summary);

	//
	//for (int i = 0; i < 3; i++) {
	//	angle[i] = angle_ini[i];
	//}

	Eigen::Matrix<double, 3, 3> matR1;
	matR1 = Eigen::AngleAxis<double>(angle[2] * M_PI / 180.0, Eigen::Matrix<double, 3, 1>::UnitY())
		* Eigen::AngleAxis<double>(angle[1] * M_PI / 180.0, Eigen::Matrix<double, 3, 1>::UnitX())
		* Eigen::AngleAxis<double>(angle[0] * M_PI / 180.0, Eigen::Matrix<double, 3, 1>::UnitZ());

	for (int i = 0; i < 9; i++) {
		matR[i] = matR1(i / 3, i % 3);
	}

	return 0;
}

