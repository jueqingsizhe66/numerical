#include "header.h"

using std::cout;

int main(void)
{
	// All basic variables are stored in the Settings object.
	Settings settings;

	// Domain boundaries, starting at (0,0,0)
	settings.l_x = 1;
	settings.l_y = 1;
	settings.l_z = 1;
	
	// Number of partitions, per direction
	settings.p_x = 100;
	settings.p_y = 100;
	settings.p_z = 100;

	// Resulting delta sizes, per direction
	settings.calculate_deltas();
	
	// alpha for 340a Stainless Steel (m^2/s)
	settings.alpha = .001; //4.2E-6;

	// time step
	settings.dt = 0.0005;

	// number of iterations
	settings.nsteps = 100;

	settings.print();
	// Finished Initializing Settings.

	// Initializes Domain
	Domain T ( settings );
	
	FTCS( T );	
	
	return 0;
}
