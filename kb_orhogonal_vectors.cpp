#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "kb_orhogonal_vectors.h"
#include "kb_mat.h"

int kb::orthogonalVectors(
	double vec_z[3],
	double vec_x[3],
	double vec_y[3]
)
{
	double uvec_z[3];	kb::vec_unit(vec_z, uvec_z, 3);
	double ux[3] = { 1,0,0 };
	double uy[3] = { 0,1,0 };
	double uz[3] = { 0,0,1 };

	double dpx = kb::dotproduct(uvec_z, ux, 3); if (dpx < 0) { dpx = -dpx; }
	double dpy = kb::dotproduct(uvec_z, uy, 3); if (dpy < 0) { dpy = -dpy; }
	double dpz = kb::dotproduct(uvec_z, uz, 3); if (dpz < 0) { dpz = -dpz; }

	double ux2[3], uy2[3];
	if (dpx <= dpy && dpx <= dpz) {
		kb::crossproduct(uvec_z, ux, ux2);
		kb::crossproduct(uvec_z, ux2, uy2);
	}
	else if (dpy <= dpx && dpy <= dpz) {
		kb::crossproduct(uvec_z, uy, ux2);
		kb::crossproduct(uvec_z, ux2, uy2);
	}
	else if (dpz <= dpx && dpz <= dpy) {
		kb::crossproduct(uvec_z, uz, ux2);
		kb::crossproduct(uvec_z, ux2, uy2);
	}

	//	Œ‹‰ÊŠi”[
	kb::vec_unit(ux2, vec_x, 3);
	kb::vec_unit(uy2, vec_y, 3);

	return 0;
}

int kb::orthogonalVectors(
	double vec_z[3],
	double vec_x_near[3],
	double vec_x[3],
	double vec_y[3]
)
{
	double uvec_z[3];	kb::vec_unit(vec_z, uvec_z, 3);

	{
		double ux2[3];
		double uy2[3];
		kb::crossproduct(uvec_z, vec_x_near, uy2);
		kb::crossproduct(uy2, uvec_z, ux2);

		kb::vec_unit(ux2, vec_x, 3);
	}

	kb::crossproduct(uvec_z, vec_x, vec_y);

	return 0;
}

int kb::orthogonalVectors(
	double vec_x0[3],
	double vec_y0[3],
	double vec_z0[3],
	double vec_z1[3],
	double vec_x1[3],
	double vec_y1[3]
)
{
	double uvec_z0[3];	kb::vec_unit(vec_z0, uvec_z0, 3);
	double uvec_z1[3];	kb::vec_unit(vec_z1, uvec_z1, 3);

	double rotz[3];
	kb::crossproduct(uvec_z0, uvec_z1, rotz);
	double sin_theta = kb::vec_length(rotz, 3);

	if (sin_theta < -1.0 || 1.0 < sin_theta) {
		std::cout << "error sin_teta: " << sin_theta << std::endl;
	}

	if (sin_theta < 0.01) {
		return kb::orthogonalVectors(vec_z1, vec_x0, vec_x1, vec_y1);
	}

	double uvec_rotz[3];	kb::vec_unit(rotz, uvec_rotz, 3);

	double deg = 180.0*asin(sin_theta) / M_PI;
	double qt1[4];
	kb::qtn_dir2dq(rotz, deg, qt1);

	double matR[9];
	kb::qtn_Q2R(qt1, matR);

	kb::matmul_3x3_3x1(matR, vec_x0, vec_x1);
	kb::matmul_3x3_3x1(matR, vec_y0, vec_y1);


	return 0;
}


int kb::orthogonalVectors(
	double vec_x0[3],
	double vec_y0[3],
	double vec_z0[3],
	double vec_z1[3],
	double vec_x1[3],
	double vec_y1[3],
	double thres_deg
)
{
	double uvec_z0[3];	kb::vec_unit(vec_z0, uvec_z0, 3);
	double uvec_z1[3];	kb::vec_unit(vec_z1, uvec_z1, 3);

	double rotz[3];
	kb::crossproduct(uvec_z0, uvec_z1, rotz);
	double sin_theta = kb::vec_length(rotz, 3);

	if (sin_theta < -1.0 || 1.0 < sin_theta) {
		std::cout << "error sin_teta: " << sin_theta << std::endl;
	}

	if (sin_theta < 0.01) {
		return kb::orthogonalVectors(vec_z1, vec_x0, vec_x1, vec_y1);
	}


	double uvec_rotz[3];	kb::vec_unit(rotz, uvec_rotz, 3);

	double deg = 180.0*asin(sin_theta) / M_PI;
	if (deg > thres_deg) {
		deg = thres_deg;
	}
	double qt1[4];
	kb::qtn_dir2dq(rotz, deg, qt1);

	double matR[9];
	kb::qtn_Q2R(qt1, matR);

	kb::matmul_3x3_3x1(matR, vec_x0, vec_x1);
	kb::matmul_3x3_3x1(matR, vec_y0, vec_y1);
	kb::matmul_3x3_3x1(matR, vec_z0, vec_z1);


	return 0;
}
