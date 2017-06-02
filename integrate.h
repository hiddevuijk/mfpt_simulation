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



// calculate the first passage time
double fpt(std::vector<double>& r,std::vector<double>& dr,
		std::vector<double>& p, std::vector<double>& dp,
		Deriv& deriv,double dt)
{
	double a = deriv.get_a();	// radius of inner boundary
	double R = deriv.get_R();	// radius of outer boundary
	double t = 0;				// first passage time
	double l = len_vec(r);		// particle distance from origin

	// let particle diffuse until it hits the inner boundary
	while(l > a) {
		// calculate new position
		deriv(r,dr,p,dp,dt);

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


// integrate time step dt
// this uses an outer, reflecting boundary only.
void integrate(std::vector<double>& r,std::vector<double>& dr,
		std::vector<double>& p, std::vector<double>& dp,
		Deriv& deriv,double dt)
{
	// radius of outer, reflecting boundary
	double R = deriv.get_R();

	// calculate step
	deriv(r,dr,p,dp,dt);

	// if particle steps outside boundary, reflect
	if (len_vec(r) > R) {
		subtr_of(r,dr);
		reflection(r,dr,R);
	}

	normalize(p);


}


// integrate SDE from t_min to t_max in time steps dt
// otherwise this does the sime as the previous funtion
void integrate(std::vector<double>& r,std::vector<double>& dr,
		std::vector<double>& p, std::vector<double>& dp,
		Deriv& deriv,double t_min, double t_max,double dt)
{
	double R = deriv.get_R();


	while(t_min+dt<t_max) {
		deriv(r,dr,p,dp,dt);
		if (len_vec(r) > R) {
			subtr_of(r,dr);
			reflection(r,dr,R);
		}
		normalize(p);
		t_min += dt;
	}
	if(t_min<t_max) {
		dt = t_max-t_min;
		deriv(r,dr,p,dp,dt);
		if (len_vec(r) > R) {
			subtr_of(r,dr);
			reflection(r,dr,R);
		}
		normalize(p);
		t_min += dt;
	}
}




#endif
