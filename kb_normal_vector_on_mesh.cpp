#include "kb_normal_vector_on_mesh.h"
#include "kb_mat.h"
#include <iostream>

int kb::normal_vector_on_mesh(
	std::vector<float>& p3d,
	std::vector<int>& face_n,
	std::vector<float>& nv_f
)
{
	std::vector< float > nv;

	return kb::normal_vector_on_mesh(p3d, face_n, nv, nv_f);
}

int kb::normal_vector_on_mesh(
	std::vector<float>& p3d,
	std::vector<int>& face_n,
	std::vector< float >& nv,
	std::vector<float>& nv_f
)
{
	std::cout << "kb::normal_vector_on_mesh()" << std::endl;

	int num_f = face_n.size() / 3;
	if (num_f <= 0)
		return 0;

	int num_n = p3d.size() / 3;

	float eps = 1.0E-6;

	nv.clear();
	nv.resize(num_n * 3, 0.0);
	nv_f.clear();
	nv_f.resize(num_f * 3, 0.0);

	for (int k = 0; k < num_f; k++) {
		int k3 = k * 3;
		int ii1 = face_n[k3] ;
		int ii2 = face_n[k3 + 1] ;
		int ii3 = face_n[k3 + 2] ;

		if (ii1 < 0 || ii2 < 0 || ii3 < 0 || ii1 >= num_n || ii2 >= num_n || ii3 >= num_n) {
			std::cout << "error: " << ii1 << " " << ii2 << " " << ii3 << std::endl;
			continue;
		}
		int i1 = ii1 * 3;
		int i2 = ii2 * 3;
		int i3 = ii3 * 3;


		double v1[3] = { p3d[i2] - p3d[i1], p3d[i2 + 1] - p3d[i1 + 1], p3d[i2 + 2] - p3d[i1 + 2] };
		double v2[3] = { p3d[i3] - p3d[i1], p3d[i3 + 1] - p3d[i1 + 1], p3d[i3 + 2] - p3d[i1 + 2] };
		double v3[3];
		kb::crossproduct(v1, v2, v3);
		double uv3[3];
		kb::vec_unit(v3, uv3, 3);

		nv_f[k3 + 0] = uv3[0];
		nv_f[k3 + 1] = uv3[1];
		nv_f[k3 + 2] = uv3[2];

		nv[i1 + 0] += uv3[0]; nv[i1 + 1] += uv3[1]; nv[i1 + 2] += uv3[2];
		nv[i2 + 0] += uv3[0]; nv[i2 + 1] += uv3[1]; nv[i2 + 2] += uv3[2];
		nv[i3 + 0] += uv3[0]; nv[i3 + 1] += uv3[1]; nv[i3 + 2] += uv3[2];
	}

	for (int k = 0; k < num_n; k++) {
		int k3 = k * 3;
		float d = sqrt(nv[k3 + 0] * nv[k3 + 0] + nv[k3 + 1] * nv[k3 + 1] + nv[k3 + 2] * nv[k3 + 2]);
		if (d < eps)
			continue;
		nv[k3 + 0] = nv[k3 + 0] / d;
		nv[k3 + 1] = nv[k3 + 1] / d;
		nv[k3 + 2] = nv[k3 + 2] / d;
	}
	return 0;
}
