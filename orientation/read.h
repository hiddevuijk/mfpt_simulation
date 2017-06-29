#ifndef GUARD_read_h
#define GUARD_read_h

#include <string>
#include <fstream>
#include <iostream>

using namespace std;
void read_variables(int& mfpt, double& r0, double& Dr,double& Dt, double& c, double& vavg,
		double& d, double& a, double& R,double& dt, int& N, int& seed,
		std::string& name, std::string fileName)
{
	std::string temp;
	std::ifstream infile(fileName);

	infile >>temp;
	infile >> mfpt;
	infile >>temp;
	infile >> r0;
	infile >>temp;
	infile >> Dr;
	infile >>temp;
	infile >> Dt;
	infile >>temp;
	infile >> c;
	infile >>temp;
	infile >> vavg;
	infile >>temp;
	infile >> d;
	infile >>temp;
	infile >> a;
	infile >>temp;
	infile >> R;
	infile >>temp;
	infile >> dt;
	infile >>temp;
	infile >> N;
	infile >>temp;
	infile >> seed;
	infile >>temp;
	infile >> name;
	
}


#endif

