#include "kb_cv_io_ply_cvmat.h"
#include "kb_make_lattice_points_3d.h"

int kb::save_Mat_8UC3_as_edge_ply(std::string& path, cv::Mat& mat)
{
	cv::Size sz = mat.size();

	std::vector<double> vpts;
	std::vector<int> vedges;
	kb::make_lattice_points_and_edges_3d(sz.width, sz.height, 0, 0, 1.0, 1.0, vpts, vedges);

	int cntn = vpts.size() / 3;
	int cnte = vedges.size() / 2;

	std::ofstream f(path);

	if (f.is_open() == false)
		return -1;



	f << "ply" << std::endl;
	f << "format ascii 1.0" << std::endl;
	f << "element vertex " << cntn << std::endl;
	f << "property float x" << std::endl;
	f << "property float y" << std::endl;
	f << "property float z" << std::endl;
	f << "property uchar red" << std::endl;
	f << "property uchar green" << std::endl;
	f << "property uchar blue" << std::endl;
	f << "element edge " << cnte << std::endl;
	f << "property int vertex1" << std::endl;
	f << "property int vertex2" << std::endl;
	f << "end_header" << std::endl;

	for (int k = 0; k < cntn; k++) {
		int k_3 = k * 3;
		int x = k % sz.width;
		int y = k / sz.width;
		cv::Vec3b color=mat.at <cv::Vec3b>(y, x);
		f << vpts[k_3 + 0] << " "
			<< vpts[k_3 + 1] << " "
			<< vpts[k_3 + 2] << " "
			<< (int)color[2] << " "
			<< (int)color[1] << " "
			<< (int)color[0] << " "
			<< std::endl;
	}
	for (int k = 0; k < cnte; k++) {
		f << vedges[k * 2] << " " << vedges[k * 2 + 1] << std::endl;
	}

	return 0;
}

int kb::save_Mat_8UC3_as_quadrilateral_mesh_ply(std::string& path, cv::Mat& mat)
{
	cv::Size sz = mat.size();

	std::vector<double> vpts;
	std::vector<int> vfaces;
	kb::make_lattice_points_and_quadrilateral_faces_3d(sz.width, sz.height, 0, 0, 1.0, 1.0, vpts, vfaces);

	int cntn = vpts.size() / 3;
	int cnte = vfaces.size() / 4;

	std::ofstream f(path);

	if (f.is_open() == false)
		return -1;



	f << "ply" << std::endl;
	f << "format ascii 1.0" << std::endl;
	f << "element vertex " << cntn << std::endl;
	f << "property float x" << std::endl;
	f << "property float y" << std::endl;
	f << "property float z" << std::endl;
	f << "property uchar red" << std::endl;
	f << "property uchar green" << std::endl;
	f << "property uchar blue" << std::endl;
	f << "element face " << cnte << std::endl;
	f << "property list uchar int vertex_indices" << std::endl;
	f << "end_header" << std::endl;

	for (int k = 0; k < cntn; k++) {
		int k_3 = k * 3;
		int x = k % sz.width;
		int y = k / sz.width;
		cv::Vec3b color = mat.at <cv::Vec3b>(y, x);
		f << vpts[k_3 + 0] << " "
			<< vpts[k_3 + 1] << " "
			<< vpts[k_3 + 2] << " "
			<< (int)color[2] << " "
			<< (int)color[1] << " "
			<< (int)color[0] << " "
			<< std::endl;
	}
	for (int k = 0; k < cnte; k++) {
		f << "4 " << vfaces[k * 4] << " " << vfaces[k * 4 + 1] <<
			" " << vfaces[k * 4 + 2] << " " << vfaces[k * 4 + 3] << std::endl;
	}

	return 0;
}

int kb::save_Mat_8UC3_as_quadrilateral_mesh_ply(std::string& path, cv::Mat& mat, cv::Mat& matDepth64F, double dx, double dy, int mode_normal)
{
	cv::Size sz = mat.size();
	cv::Size sz2 = matDepth64F.size();
	if (sz != sz2)
		return -1;

	std::vector<double> vpts;
	std::vector<int> vfaces;
	kb::make_lattice_points_and_quadrilateral_faces_3d(sz.width, sz.height, 0, 0, dx, dy, vpts, vfaces);

	int cntn = vpts.size() / 3;
	int cnte = vfaces.size() / 4;

	std::ofstream f(path);

	if (f.is_open() == false)
		return -1;



	f << "ply" << std::endl;
	f << "format ascii 1.0" << std::endl;
	f << "element vertex " << cntn << std::endl;
	f << "property float x" << std::endl;
	f << "property float y" << std::endl;
	f << "property float z" << std::endl;
	f << "property uchar red" << std::endl;
	f << "property uchar green" << std::endl;
	f << "property uchar blue" << std::endl;
	f << "element face " << cnte << std::endl;
	f << "property list uchar int vertex_indices" << std::endl;
	f << "end_header" << std::endl;

	for (int k = 0; k < cntn; k++) {
		int k_3 = k * 3;
		int x = k % sz.width;
		int y = k / sz.width;
		cv::Vec3b color = mat.at <cv::Vec3b>(y, x);
		double depth=matDepth64F.at<double>(y, x);
		f << vpts[k_3 + 0] << " "
			<< vpts[k_3 + 1] << " "
			<< depth << " "
			<< (int)color[2] << " "
			<< (int)color[1] << " "
			<< (int)color[0] << " "
			<< std::endl;
	}
	for (int k = 0; k < cnte; k++) {
		if (mode_normal == 0) {
			f << "4 " << vfaces[k * 4] << " " << vfaces[k * 4 + 1] <<
				" " << vfaces[k * 4 + 2] << " " << vfaces[k * 4 + 3] << std::endl;
		}
		else {
			f << "4 " << vfaces[k * 4] << " " << vfaces[k * 4 + 3] <<
				" " << vfaces[k * 4 + 2] << " " << vfaces[k * 4 + 1] << std::endl;
		}
	}

	return 0;
}
