// 3D Heat DIffusion Equation Solver

#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
	// Domain boundaries, starting at (0,0,0)
	double l_x = 1;
	double l_y = 1;
	double l_z = 1;
	
	// Number of partitions, per direction
	int p_x = 100;
	int p_y = 100;
	int p_z = 100;

	// Resulting delta sizes, per direction
	double dx = l_x / p_x;
	double dy = l_y / p_y;
	double dz = l_z / p_z;
	
	// the 3D vector domain
	vector<vector<vector<double> > > domain; 
	domain.resize(p_x);
	for( int i = 0; i < p_x; i++ )
	{	
		domain[i].resize(p_y);
		for( int j = 0; j < p_y; j++ )
			domain[i][j].resize(p_z);
	}

	// alpha for 340a Stainless Steel (m^2/s)
	double alpha = 4.2E-6;

	// time step
	double dt = 0.005;

	// number of iterations
	int nsteps = 100000;


}
