#include <vector>

#pragma once

namespace kb
{
	int normal_vector_on_mesh(
		std::vector<float>& p3d,
		std::vector<int>& face_n,
		std::vector< float >& nv,
		std::vector<float>& nv_f
	);
	int normal_vector_on_mesh(
		std::vector<float>& p3d,
		std::vector<int>& face_n,
		std::vector<float>& nv_f
	);
};
