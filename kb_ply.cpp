#include <fstream>
#include <io.h>
#include <iostream>
#include <sstream>

#include "kb_ply.h"
#include "kb_mat.h"


int kb::save_pt3d_as_ply(
	std::string& path,
	std::vector<float>& v_pt,
	std::vector<unsigned char>& vcolor)
{
	int num = v_pt.size() / 3;
	if (num < 1)
		return -1;
	int num2 = vcolor.size() / 3;
	if (num != num2)
		return -1;

	{
		std::ofstream file(path);

		file << "ply" << std::endl;
		file << "format ascii 1.0" << std::endl;
		file << "element vertex " << num << std::endl;
		file << "property float x" << std::endl;
		file << "property float y" << std::endl;
		file << "property float z" << std::endl;
		file << "property uchar red" << std::endl;
		file << "property uchar green" << std::endl;
		file << "property uchar blue" << std::endl;
		file << "end_header" << std::endl;
		for (int k = 0; k < num; k++) {
			file << v_pt[k * 3] << " " << v_pt[k * 3 + 1] << " " << v_pt[k * 3 + 2] << " " <<
				(int)vcolor[k * 3] << " " << (int)vcolor[k * 3 + 1] << " " << (int)vcolor[k * 3 + 2] << std::endl;
		}

	}

	return 0;
}

int kb::save_pt3d_as_ply(
	std::string& path,
	std::vector<float>& v_pt)
{
	int num = v_pt.size() / 3;
	if (num < 1)
		return -1;

	{
		std::ofstream file(path);

		file << "ply" << std::endl;
		file << "format ascii 1.0" << std::endl;
		file << "element vertex " << num << std::endl;
		file << "property float x" << std::endl;
		file << "property float y" << std::endl;
		file << "property float z" << std::endl;
		file << "end_header" << std::endl;
		for (int k = 0; k < num; k++) {
			file << v_pt[k * 3] << " " << v_pt[k * 3 + 1] << " " << v_pt[k * 3 + 2] << std::endl;
		}

	}

	return 0;
}



