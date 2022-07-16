#include <vector>

#pragma once

namespace kb
{

	int centerline2tube(
		std::vector<double>& vec_pos,
		std::vector<double>& o_vec_vz,
		std::vector<double>& o_vec_r,
		int num_sample,
		std::vector< double >& circum
	);

	int tube2tube(
		std::vector<double>& circum,
		std::vector<double>& vec_vz,
		int num_sample,
		std::vector<double>& o_circum,
		int max_iter
	);

};