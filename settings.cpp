#include "header.h"

void Settings::calculate_deltas(void)
{
	dx = l_x / p_x;
	dy = l_y / p_y;
	dz = l_z / p_z;
};

void Settings::print(void)
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
	cout << "	Boundary Conditions: ";
	if( dirichilet )
		cout << "Dirichilet";
	else
		cout << "Periodic";
	cout << endl;
}
