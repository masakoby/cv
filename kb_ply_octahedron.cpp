#include "kb_ply_octahedron.h"

int kb::make_octahedron(
	std::vector<float>& pt3d,
	std::vector<int>& vidx
)
{
	float pt[18] = {
		1,0,0,
		-1,0,0,
		0,1,0,
		0,-1,0,
		0,0,1,
		0,0,-1,
	};
	int idx[24] = {
		0,2,4,
		2,1,4,
		1,3,4,
		3,0,4,
		0,5,2,
		2,5,1,
		1,5,3,
		3,5,0
	};
	pt3d.resize(18, 0);
	vidx.resize(24, 0);

	for (int i = 0; i < 18; i++) {
		pt3d[i] = pt[i];
	}
	for (int i = 0; i < 24; i++) {
		vidx[i] = idx[i];
	}
	return 0;
}
