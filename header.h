#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <string>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;
using std::scientific;
using std::setw;
using std::string;

double BC( int x, int y, int z );
double dirichiletBC( int, int, int );
double periodicBC( int, int, int, int, double );
double sourceTerm( int, int, int);
vector<double> mat_mult( vector<vector<double> > A, vector<double> B );
vector<double> vec_add( vector<double> a, vector<double> b );
vector<vector<double> > mat_sub( vector<vector<double> > A, vector<vector<double> > B );
vector<vector<double> > mat_mat_mult( vector<vector<double> > A, vector<vector<double> > B );

class Settings
{
	public:
		// Domain boundaries, starting at (0,0,0)
		double l_x;
		double l_y;
		double l_z;
		// Number of partitions, per direction
		int p_x;
		int p_y;
		int p_z;
		// Resulting delta sizes, per direction
		double dx;
		double dy;
		double dz;
		// alpha for 340a Stainless Steel (m^2/s)
		double alpha; //4.2E-6;
		// time step
		double dt;
		// number of iterations
		int nsteps;
		// Boundary Conditions
		bool dirichilet;
		
		Settings() {};
		void calculate_deltas(void);
		void print(void);
};

class Domain
{
	public:
		Settings settings;
		int p_x, p_y, p_z;
		vector<vector<vector<double> > > m;
		Domain( Settings );
		void updateBC( int );
		void print( void );
		Domain& operator= (const Domain& param);
};

Domain FTCS( Domain T );
Domain CN( Domain T );
Domain Jacobi( Domain T );
Domain GS( Domain T );
void show_sample( Domain T);
