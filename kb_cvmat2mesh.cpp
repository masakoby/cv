#include "kb_cvmat2mesh.h"

int kb::cvmat2mesh(
	cv::Mat& mat1,
	std::vector<float>& v3d,
	std::vector<int>& vidx,
	float max_value
)
{
	cv::Size sz = mat1.size();
	int num_pt = sz.width * sz.height;
	v3d.resize(num_pt*3);

	float ratio = max_value / 255.0;

	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			float b1 = mat1.at<unsigned char>(j, i);
			int ii = (i + j * sz.width) * 3;
			v3d[ii + 0] = i;
			v3d[ii + 1] = j;
			v3d[ii + 2] = b1*ratio;
		}
	}

	for (int j = 0; j < sz.height-1; j++) {
		int j1 = j * sz.width;
		int j2 = (j + 1) * sz.width;
		for (int i = 0; i < sz.width-1; i++) {
			vidx.push_back(i + j1);
			vidx.push_back(i + 1 + j1);
			vidx.push_back(i + j2);

			vidx.push_back(i + j2);
			vidx.push_back(i + 1 + j1);
			vidx.push_back(i + 1 + j2);
		}
	}

	return 0;
}

int kb::cvmat2mesh_64F(
	cv::Mat& mat1,
	std::vector<float>& v3d,
	std::vector<int>& vidx
)
{
	cv::Size sz = mat1.size();
	int num_pt = sz.width * sz.height;
	v3d.resize(num_pt * 3);


	for (int j = 0; j < sz.height; j++) {
		for (int i = 0; i < sz.width; i++) {
			float b1 = mat1.at<double>(j, i);
			int ii = (i + j * sz.width) * 3;
			v3d[ii + 0] = i;
			v3d[ii + 1] = j;
			v3d[ii + 2] = b1;
		}
	}

	for (int j = 0; j < sz.height - 1; j++) {
		int j1 = j * sz.width;
		int j2 = (j + 1) * sz.width;
		for (int i = 0; i < sz.width - 1; i++) {
			vidx.push_back(i + j1);
			vidx.push_back(i + 1 + j1);
			vidx.push_back(i + j2);

			vidx.push_back(i + j2);
			vidx.push_back(i + 1 + j1);
			vidx.push_back(i + 1 + j2);
		}
	}

	return 0;
}
