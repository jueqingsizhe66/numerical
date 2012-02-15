#include "header.h"

int main(void)
{
	// All basic variables are stored in the Settings object.
	Settings settings;

	// Domain boundaries, starting at (0,0,0)
	settings.l_x = 1;
	settings.l_y = 1;
	settings.l_z = 1;
	
	// Number of partitions, per direction
	settings.p_x = 10;
	settings.p_y = 10;
	settings.p_z = 10;

	// Resulting delta sizes, per direction
	settings.calculate_deltas();
	
	// alpha for 340a Stainless Steel (m^2/s)
	settings.alpha = .001; //4.2E-6;

	// time step
	settings.dt = 0.005;

	// number of iterations
	settings.nsteps = 10000;

	// Boundary conditions
	settings.dirichilet = true;

	settings.print();
	// Finished Initializing Settings.

	// Initializes Domain
	Domain T ( settings );
	
	// Runs a solver on the Domain.
	// 	1 for FTCS
	// 	2 for Crank-Nicolson
	int solver = 2;

	if( solver == 1 )
		FTCS(T);
	else
		CN(T);
	
	return 0;
}
