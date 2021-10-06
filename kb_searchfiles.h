#include <string>
#include <vector>

#pragma once

namespace kb
{
	int search_files(
		const std::string iDirname,
		const char* iStrext1,
		std::vector<std::string>& oVec1
	);

};