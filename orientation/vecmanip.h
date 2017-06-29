#ifndef GUARD_vecmanip_h
#define GUARD_vecmanip_h

/* 
 * some functions to manipulate std vectors
*/


#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

double dot(const std::vector<double>& a,
		const std::vector<double>& b)
{
	int N = a.size();
	double temp =0;
	for(int i=0;i<N;i++)	
		temp += a[i]*b[i];
	return temp;
}


// returns the length of a vector
double len_vec(const std::vector<double>& a)
{
	double s =0;
	int n = a.size();
	for( int i=0; i<n;++i)
		s += a[i]*a[i];
	return std::sqrt(s);
}

// normalize a vector to length m
// default m=1/
void normalize(std::vector<double>& a,double m = 1.)
{
	double l = len_vec(a);
	int n = a.size();
	for(int i=0;i<n;++i) {
		a[i] /= l;
		a[i] *= m;
	}
}

// create a new vector with entries ci = ai + bi
std::vector<double> add(const std::vector<double>& a,
		const std::vector<double>& b)
{
	int s = a.size();
	std::vector<double> c(s);
	for( int i=0;i<s;++i)
		c[i] = a[i] + b[i];
	return c;

}

// add vector b to vector a
void add_to(std::vector<double>& a,
		const std::vector<double>& b)
{
	int s = a.size();
	for( int i=0;i<s;++i)
		a[i] += b[i];

}

// create new vector with entries ci = ai - bi
std::vector<double> subtr(const std::vector<double>& a,
		const std::vector<double>& b)
{
	int s = a.size();
	std::vector<double> c(a);
	for( int i=0;i<s;++i)
		c[i] = a[i] - b[i];
	return c;

}

// subtract vector b from a
void subtr_of(std::vector<double>& a,
		const std::vector<double>& b)
{
	int s = a.size();
	for( int i=0;i<s;++i)
		a[i] -= b[i];

}

// print vector using cout
void print_vec(std::vector<double>& v,int N = 0)
{
	if (N==0) N = v.size();
	for(int i=0;i<N;++i)
		std::cout << v[i] << std::endl;
}

// write vector to a file named fileName.
// writes values separated by newline
// write N values, default N = v.size()
void write_vec(std::vector<double> v,std::string fileName, int N = 0)
{
	if(N==0) N = v.size();
	std::ofstream out;
	out.open(fileName);
	for(int i=0;i<N;++i)
		out<<v[i] << '\n';
}


// write vector to a file named fileName.
// writes values separated by newline
// write N values, default N = v.size()
void write_vec(std::vector<int> v,std::string fileName, int N = 0)
{
	if(N==0) N = v.size();
	std::ofstream out;
	out.open(fileName);
	for(int i=0;i<N;++i)
		out<<v[i] << '\n';
}






#endif
