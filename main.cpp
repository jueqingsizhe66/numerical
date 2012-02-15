#include "header.h"

// This file serves as the "control panel" for the program.

// Simply change the desired variables, make, and run.

int main(int argc, char* argv[])
{
	// All basic variables are stored in the Settings object.
	Settings settings;

	// Domain boundaries, starting at (0,0,0)
	settings.l_x = 1;
	settings.l_y = 1;
	settings.l_z = 1;

	// PROBLEM SIZE - for cubic domain of size n, set
	// n = p_x = p_y = p_z	
	// Number of partitions, per direction
	settings.p_x = 10;
	settings.p_y = 10;
	settings.p_z = 10;

	// Resulting delta sizes, per direction
	settings.calculate_deltas();
	
	// alpha
	settings.alpha = .001;

	// time step
	settings.dt = 0.005;

	// number of iterations
	settings.nsteps = 100;

	// Boundary conditions
	// Set dirichilet to true for dirichilet conditions
	// Set dirichilet to false for periodic condtions
	// **NOTE** - BC functions can be defined in boundary.cpp
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
