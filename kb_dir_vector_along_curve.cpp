#include "kb_dir_vector_along_curve.h"

void kb::dir_vector_along_curve(std::vector<double>& vpos, std::vector<double>& vdir)
{
	int num_pos = vpos.size() / 3;
	vdir.resize(num_pos * 3, 0);

	if (num_pos <= 1)
		return;

	for (int k = 0; k < num_pos; k++) {
		int k3 = k * 3;
		int k3bf = (k - 1) * 3;
		int k3af = (k + 1) * 3;
		if (k== 0) {
			k3bf = 0;
		}
		if (k == (num_pos - 1)) {
			k3af = k3;
		}
		double x = vpos[k3af + 0] - vpos[k3bf + 0];
		double y = vpos[k3af + 1] - vpos[k3bf + 1];
		double z = vpos[k3af + 2] - vpos[k3bf + 2];
		double d = sqrt(x * x + y * y + z * z);
		if (d < 1.0E-6)
			continue;

		vdir[k3 + 0] = x / d;
		vdir[k3 + 1] = y / d;
		vdir[k3 + 2] = z / d;
	}
}
