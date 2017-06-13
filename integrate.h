#ifndef GUARD_integrate_h
#define GUARD_integrate_h

/*
 * Integrate an SDE using the Deriv object.
 * Also calculate the first passage time
*/

#include "vecmanip.h"
#include "deriv.h"
#include "reflection.h"
#include <assert.h>

// Calculate the first passage time of reaching the inner
// boundary.
// With a reflecting outer boundary (radius R) and 
// an absorbing inner boundary (radius a).
double fpt(std::vector<double>& r,std::vector<double>& dr,
		std::vector<double>& p, std::vector<double>& dp,
		Deriv& deriv,double dt,double a,double R)
{
	double t = 0;			// first passage time
	double l = len_vec(r);		// particle distance from origin

	// let particle diffuse until it hits the inner boundary
	while(l > a) {
		// calculate new position
		deriv(r,dr,p,dp,dt);
		add_to(r,dr);
		add_to(p,dp);

		// new dist. from origin
		l = len_vec(r);

		// if l > R the particle is ouside the outer
		// boundary: reflect the particle s.t. l < R
		if (l > R) {
			// undo last increment
			subtr_of(r,dr);
			//reflect
			reflection(r,dr,R);
			// new length
			l = len_vec(r);

			// if l>R, an numerical error has occured 
			// during the reflection: the particle is
			// still outside the outer boundary.
			// stop this run and return t=0 to signal
			// the error
			if(l>R){
				t = 0;
				break;
			}
		}

		// normalize p to 1
		normalize(p);

		t += dt;
	}
	// return total time before absorbtion on inner boundary
	return t;

}




// Integrate deriv over a time dt
// with a reflecting outer boundary with radius R
void integrate_outer_refl(std::vector<double>& r, std::vector<double>& dr,
	std::vector<double>& p, std::vector<double>& dp,
	Deriv& deriv, double dt, double R)
{
	deriv(r,dr,p,dp,dt);
	double l = len_vec(r);

	// if the particle is placed outside 
	// the outer radius, reflec.
	if(l > R) {
		reflection(r,dr,R);
		l = len_vec(r);
	}
		
}




#endif
