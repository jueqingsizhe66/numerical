#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

double BC( int x, int y, int z );

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
		
		Settings() {};

		void calculate_deltas(void)
		{
			dx = l_x / p_x;
			dy = l_y / p_y;
			dz = l_z / p_z;
		};

		void print(void)
		{
			cout << "Settings Summary" << endl;
			cout << "----------------" << endl;
			cout << "	Domain Boundaries (l_x, l_y, l_z): (";
			cout << l_x << " " << l_y << " " << l_z << ")" << endl;
			cout << "	Number of Partitions (p_x, p_y, p_z): (";
			cout << p_x << " " << p_y << " " << p_z << ")" << endl;
			cout << "	Deltas (dx, dy, dz): (";
			cout << dx << " " << dy << " " << dz << ")" << endl;
			cout << "	Alpha: " << alpha << endl;
			cout << "	Timestep (dt): " << dt << endl;
			cout << "	Number of Iterations:" << nsteps << endl;
		}
};

class Domain
{
	public:
		Settings settings;
		int p_x, p_y, p_z;
		vector<vector<vector<double> > > m;
		Domain( Settings );
		void print( void );
		Domain& operator= (const Domain& param);
};

Domain FTCS( Domain T );

/*
ostream & operator<<(ostream &out, const Settings &S)
{
	out << "Settings Summary" << endl;
	out << "----------------" << endl;
	out << "	Domain Boundaries (l_x, l_y, l_z): (";
	out << S.l_x << " " << S.l_y << " " << S.l_z << ")" << endl;
	out << "	Number of Partitions (p_x, p_y, p_z): (";
	out << S.p_x << " " << S.p_y << " " << S.p_z << ")" << endl;
	out << "	Deltas (dx, dy, dz): (";
	out << S.dx << " " << S.dy << " " << S.dz << ")" << endl;
	out << "	Alpha: " << S.alpha << endl;
	out << "	Timestep (dt): " << S.dt << endl;
	out << "	Number of Iterations:" << S.nsteps << endl;
	return out;
}
*/
