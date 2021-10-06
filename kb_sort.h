#include <vector>
#include <string>

#pragma once

namespace kb
{
	int sort(
		std::vector<int>& vvalues,
		std::vector<int>& vidx,
		int order//	0=¸‡, 1=~‡
	);
	int sort(
		std::vector<std::string>& vvalues,
		std::vector<int>& vidx,
		int order//	0=¸‡, 1=~‡
	);
};
