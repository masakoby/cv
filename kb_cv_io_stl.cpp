#include "kb_cv_io_stl.h"
#include "kb_cvmat2mesh.h"
#include "kb_stl.h"

int kb::saveAsSTL_64F(
	const std::string& path1,
	cv::Mat& mat64F
)
{
	std::vector<float> v3d;
	std::vector<int> vidx;

	kb::cvmat2mesh_64F(mat64F, v3d, vidx);

	kb::saveAsSTL(path1, v3d, vidx);


	return 0;
}
