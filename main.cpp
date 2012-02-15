#include "header.h"

int main(int argc, char* argv[])
{
	// All basic variables are stored in the Settings object.
	Settings settings;

	// Domain boundaries, starting at (0,0,0)
	settings.l_x = 1;
	settings.l_y = 1;
	settings.l_z = 1;
	
	// Number of partitions, per direction
	settings.p_x = 20;
	settings.p_y = 20;
	settings.p_z = 20;

	// Resulting delta sizes, per direction
	settings.calculate_deltas();
	
	// alpha for 340a Stainless Steel (m^2/s)
	settings.alpha = .001; //4.2E-6;

	// time step
	settings.dt = 0.005;

	// number of iterations
	settings.nsteps = 100;

	// Boundary conditions
	settings.dirichilet = true;

	settings.print();
	// Finished Initializing Settings.

	// Initializes Domain
	Domain T ( settings );
	
	// Solver selection - runs the selected solver on Domain.
	// 	Default is FTCS
	// 	Command line argument "-CN" is for Crank-Nocolson
	if( argc > 1 )
	{
		string s = "-CN";
		if( s.compare( argv[1] ) == 0 )
		{	
			CN(T);
			return 0;
		}
	}
	else
		FTCS(T);
	
	return 0;
}
