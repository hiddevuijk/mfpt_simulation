#ifndef GUARD_deriv_h
#define GUARD_deriv_h

/* 
 * object with the SDE
 * the integrarion within a sphere
 * is done in integration.h
 */


#include <cmath>
#include <vector>
#include <random>
#include <iostream>

struct Deriv {
	public:

	Deriv(double Dtt, double Drr, double cc,double vavgg, double dd,
			std::normal_distribution<double> ndistt,
			std::default_random_engine generatorr) : 
			sqrt_2Dt(std::sqrt(2*Dtt)), sqrt_2Dr(std::sqrt(2*Drr)),
			c(cc),vavg(vavgg), d(dd), ndist(ndistt), generator(generatorr){}

	// calculate derivatives and new positions
	void operator() (const std::vector<double>& r, std::vector<double>& dr,
			const std::vector<double>& p, std::vector<double>& dp, double dt);

	double get_d(){ return d;}
	double get_c(){ return c;}

	private:
	double sqrt_2Dt;	// sqrt(2*Dt)
	double sqrt_2Dr;	// sqrt(2*Dr)
	double c;		// strength of the activity field
	double vavg;
	double d;		// strength of the torque (neg. is aligning w. grad. v0)

	// radial dependent activity, and its radial derivative
	double v(double r) { return c/(r*r);}
	double dvdr(double r){ return -2*c/(r*r*r);}

	// random number generator
	std::default_random_engine generator;
	std::normal_distribution<double> ndist;
};


// The () operator calculates the increment in r and p (dr and dp) at r,p
// for a time increment dt.
void Deriv::operator() (const std::vector<double>& r, std::vector<double>& dr,
		const std::vector<double>& p, std::vector<double>& dp, double dt)
{
	if(vavg < 1.e-10) {
		double sqrt_dt = std::sqrt(dt);
		double etaX, etaY, etaZ;
		double l = len_vec(r);
		double v0 = v(l);

		// claculate r increment
		dr[0] = v0*p[0]*dt + ndist(generator)*sqrt_dt*sqrt_2Dt;
		dr[1] = v0*p[1]*dt + ndist(generator)*sqrt_dt*sqrt_2Dt;
		dr[2] = v0*p[2]*dt + ndist(generator)*sqrt_dt*sqrt_2Dt;
		

		// calculate p increment
		etaX = ndist(generator)*sqrt_dt*sqrt_2Dr;
		etaY = ndist(generator)*sqrt_dt*sqrt_2Dr;
		etaZ = ndist(generator)*sqrt_dt*sqrt_2Dr;
		dp[0] = (etaY*p[2] - etaZ*p[1]);
		dp[1] = (etaZ*p[0] - etaX*p[2]);
		dp[2] = (etaX*p[1] - etaY*p[0]);

		// add torque
		if(std::fabs(d) >  1.e-10) { 
			double dvdr0 = dvdr(l);

			// rx,ry,rz is the unit vector in the direct of the vector r
			double phi = std::atan2(r[1],r[0]);
			double theta = std::acos(r[2]/l);
			double rx = std::sin(theta)*std::cos(phi);
			double ry = std::sin(theta)*std::sin(phi);
			double rz = std::cos(theta);

			// torque = d* p cross (p cross del v). Del v is dvdr in the r direction
			dp[0] += dt*d*dvdr0*(-(p[1]*p[1]+p[2]*p[2])*rx - p[0]*p[1]*ry + p[0]*p[2]*rz);
			dp[1] += dt*d*dvdr0*(-p[0]*p[1]*rx - (p[0]*p[0]+p[2]*p[2])*ry + p[1]*p[2]*rz);
			dp[2] += dt*d*dvdr0*(p[0]*p[2]*rx + p[1]*p[2]*ry - (p[0]*p[0]+p[2]*p[2])*rz);
		}
	} else {
		double sqrt_dt = std::sqrt(dt);
		double etaX, etaY, etaZ;
		double l = len_vec(r);
		double v0 = vavg;

		// claculate r increment
		dr[0] = v0*p[0]*dt + ndist(generator)*sqrt_dt*sqrt_2Dt;
		dr[1] = v0*p[1]*dt + ndist(generator)*sqrt_dt*sqrt_2Dt;
		dr[2] = v0*p[2]*dt + ndist(generator)*sqrt_dt*sqrt_2Dt;
		

		// calculate p increment
		etaX = ndist(generator)*sqrt_dt*sqrt_2Dr;
		etaY = ndist(generator)*sqrt_dt*sqrt_2Dr;
		etaZ = ndist(generator)*sqrt_dt*sqrt_2Dr;
		dp[0] = (etaY*p[2] - etaZ*p[1]);
		dp[1] = (etaZ*p[0] - etaX*p[2]);
		dp[2] = (etaX*p[1] - etaY*p[0]);


	}

}


#endif
