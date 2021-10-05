
#include "kb_cv_chess2perspective_transform.h"
#include "lx_prm_system.h"
#include "kb_inifile.h"
#include "kb_searchfiles.h"
#include "kb_mat.h"
#include "kb_cv_io.h"

int kb::chess2perspective_transform(
	std::string& dname_chess,
	std::string& path_prm,
	double ratio_preproc,
	std::vector<cv::Point2f>& v_chess,
	std::vector<cv::Point2f>& v_chess2,
	cv::Mat& matP)
{

	kb::CPrm_system prm0;	prm0.load(path_prm);



	std::vector< std::string > vfname_chess;
	//std::vector<int> vchess2img;
	//std::vector < std::vector<cv::Point2f>> vv_chess;
	double ds_chess = 0.0;
	int nx = 7;
	int ny = 5;
	{
		double step_width = 4.0;
		int mode_circle = 0;
		int debug = 0;

		kb::read(path_prm.c_str(), "chessboard", "nx", nx);
		kb::read(path_prm.c_str(), "chessboard", "ny", ny);
		kb::read(path_prm.c_str(), "chessboard", "mode_circle", mode_circle);
		kb::read(path_prm.c_str(), "chessboard", "debug", debug);
		kb::read(path_prm.c_str(), "chessboard", "step_width", step_width);


		int num_c = nx * ny;
		double dx = (nx - 1) * step_width;
		double dy = (ny - 1) * step_width;
		ds_chess = sqrt(dx * dx + dy * dy);

		if (kb::search_files(dname_chess, "*_p2d.txt", vfname_chess) < 0)
			return -1;

		//	ƒJƒƒ‰”
		int num_files_chess = vfname_chess.size();
		std::cout << "num of files: " << num_files_chess << std::endl;
		//vchess2img.resize(num_files_chess, -1);
		//vv_chess.resize(num_files_chess);
		for (int k = 0; k < num_files_chess; k++) {
			std::string path1 = dname_chess + vfname_chess[k];

			std::vector<cv::Point2f> v1;
			kb::load_pt2d(path1, v1);
			int num1 = v1.size();
			if (num1 != num_c)
				continue;

			v_chess.push_back(v1[0] * ratio_preproc);
			v_chess.push_back(v1[nx - 1] * ratio_preproc);//6
			v_chess.push_back(v1[num_c - 1] * ratio_preproc);//34
			v_chess.push_back(v1[num_c - nx] * ratio_preproc);//28

			break;
			//return 0;
		}
	}

	int num_v_chess = v_chess.size();
	if (num_v_chess != 4)
		return -1;

	cv::Point2f psum1(0, 0);
	for (int i = 0; i < 4; i++) {
		psum1.x += v_chess[i].x;
		psum1.y += v_chess[i].y;
	}
	psum1.x = psum1.x * 0.25;
	psum1.y = psum1.y * 0.25;


	cv::Point2f psz1;
	{
		cv::Point2f pw1 = v_chess[0] - v_chess[1];
		cv::Point2f pw2 = v_chess[2] - v_chess[3];
		double w1 = sqrt(pw1.x * pw1.x + pw1.y * pw1.y);
		double w2 = sqrt(pw2.x * pw2.x + pw2.y * pw2.y);
		psz1.x = (w1 + w2) * 0.25;
	}
	{
		cv::Point2f ph1 = v_chess[0] - v_chess[3];
		cv::Point2f ph2 = v_chess[2] - v_chess[1];
		double h1 = sqrt(ph1.x * ph1.x + ph1.y * ph1.y);
		double h2 = sqrt(ph2.x * ph2.x + ph2.y * ph2.y);
		psz1.y = (h1 + h2) * 0.25;
	}

	{
		double rr = (double)(ny - 1) / (double)(nx - 1);
		double yy = rr * psz1.x;
		if (yy < psz1.y) {
			psz1.x = psz1.y / rr;
		}
		else {
			psz1.y = psz1.x * rr;
		}
	}

	v_chess2.resize(4);
	v_chess2[0].x = psum1.x - psz1.x;
	v_chess2[0].y = psum1.y - psz1.y;
	v_chess2[1].x = psum1.x + psz1.x;
	v_chess2[1].y = psum1.y - psz1.y;
	v_chess2[2].x = psum1.x + psz1.x;
	v_chess2[2].y = psum1.y + psz1.y;
	v_chess2[3].x = psum1.x - psz1.x;
	v_chess2[3].y = psum1.y + psz1.y;

	//cv::Mat
	//matP = cv::getPerspectiveTransform(v_chess2, v_chess);
	//cv::Mat matP_inv = cv::getPerspectiveTransform(v_chess, v_chess2);

	matP = cv::getPerspectiveTransform(v_chess, v_chess2);
	return 0;
}

