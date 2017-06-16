#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>


#include "vecmanip.h"
#include "deriv.h"
#include "integrate.h"
#include "read.h"

using namespace std;


int main(int argc, char *argv[])
{

	// define variables
	// R0: start value
	// Dr: rotational diff. const
	// Dt: translational diff. const
	// c: strength of the activity field
	// avg: if true, averaged activity is used
	// d: strength of the torque (negtive aligns with grad. v0)
	// a: inner radius (absorbing boundary)
	// R: outer radius (reflecting boundary)
	// dt: step size of integration
	// N: number of trails
	// seed: seed for the random nuber generators
	double R0,Dr,Dt,c,vavg,d,a,R,dt;
	int N,mfpt;
	int seed;

	// name of the output file
	string name;

	// name of the input file
	// default is input.txt, otherwise commandline input
	string input_name = "input.txt";
	if(argc == 2) {
		input_name = argv[1];
		input_name += ".txt";
	}
	// read variables from input file
	read_variables(mfpt,R0,Dr,Dt,c,vavg,d,a,R,dt,N,seed,name,input_name);
	// random number generator for init. values
	srand(seed);

	// position vector r
	// init. with rand values, and normalize length to R0
	vector<double> r(3);
	r[0] = 1.*rand();
	r[1] = 1.*rand();
	r[2] = 1.*rand();
	normalize(r,R0);

	// oriantation vecor p
	// init with rand values and normalize to 1.
	vector<double> p(3);
	p[0] = 1.*rand();
	p[1] = 1.*rand();
	p[2] = 1.*rand();
	normalize(p);

	// vectors with the step values
	vector<double> dr(3);
	vector<double> dp(3);

	// random number generator for integration of SDEs
	default_random_engine generator(seed);
	normal_distribution<double> ndist(0,1);

	// object for steps, increments r and p with the calculated
	// dr and dp. Relfects particle if it hits the outer boundary.
	Deriv deriv(Dt,Dr,c,vavg,d,ndist,generator);
	if(mfpt == 1) {
		// results first passage times	
		vector<double> T(N);
		for(int i=0;i<N;++i) {

			// restart with random r and p vector
			r[0] = 1.*rand();
			r[1] = 1.*rand();
			r[2] = 1.*rand();
			normalize(r,R0);

			p[0] = 1.*rand();
			p[1] = 1.*rand();
			p[2] = 1.*rand();
			normalize(p);
		
			// get FPT and save in T[i]
			T[i]= fpt_inner(r,dr,p,dp,deriv,dt,a,R);

			// if T[i] == 0, the particle was placed outside the
			// outer boundary due to a numerical error.
			// Don't use this values, and rerun run i
			if(T[i]==0) --i;
		}

		// save the fpt values in a file named 'name'
		write_vec(T,name+".dat");
	} else {
		vector<double> T(N);
		vector<int> aR(N);
		vector<double> result(2);
		for(int i=0;i<N;++i) {

			// restart with random r and p vector
			r[0] = 1.*rand();
			r[1] = 1.*rand();
			r[2] = 1.*rand();
			normalize(r,R0);

			p[0] = 1.*rand();
			p[1] = 1.*rand();
			p[2] = 1.*rand();
			normalize(p);
		
			// get FPT and save in T[i]
			result= fpt_both(r,dr,p,dp,deriv,dt,a,R);
			T[i] = result[0];
			aR[i] = result[1];	
		}

		// save the fpt values in a file named 'name'
		write_vec(T,name+"_T.dat");
		write_vec(aR,name+"_aR.dat");
	}
	return 0;
}
