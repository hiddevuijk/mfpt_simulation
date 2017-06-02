#ifndef GUARD_reflection_h
#define GUARD_reflection_h

#include <vector>
#include <cmath>
#include <assert.h>

void reflection(std::vector<double>& r1, std::vector<double>& dr,double R)
{

	double dx = dr[0];
	double dy = dr[1];
	double dz = dr[2];
	double dr_sq = dx*dx+dy*dy+dz*dz;

	double r1x = r1[0];
	double r1y = r1[1];
	double r1z = r1[2];
	double r2x = r1[0]+dr[0];
	double r2y = r1[1]+dr[1];
	double r2z = r1[2]+dr[2];

	double a = dx*dx+dy*dy+dz*dz;
	double b = 2*(dx*r1x+dy*r1y+dz*r1z);
	double c = r1x*r1x+r1y*r1y+r1z*r1z-R*R;

	double t = (-b+std::sqrt(b*b-4*a*c))/(2*a);

	double ix = r1x+dx*t;
	double iy = r1y+dy*t;
	double iz = r1z+dz*t;

	double phi = std::atan2(iy,ix);
	double theta = std::acos(iz/R);


	std::vector<double> n(3);
	n[0] = std::sin(theta)*std::cos(phi);
	n[1] = std::sin(theta)*std::sin(phi);
	n[2] = std::cos(theta);

	double d = 2*n[0]*(r2x-ix) + 2*n[1]*(r2y-iy) + 2*n[2]*(r2z-iz);

	r1[0] = r2x - d*n[0];
	r1[1] = r2y - d*n[1];
	r1[2] = r2z - d*n[2];

}







#endif
