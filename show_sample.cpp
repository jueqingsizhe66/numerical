#include "header.h"

// I use the show_sample function to keep track of whats
// going on in the domain after each iteration. I find
// that this implementation is much simpler and faster
// than exporting/importing to matlab. It accomplishes
// the same thing. While I don't get the entire view of
// the system with these sample points, I get everything
// I need to make sure its working correctly.
//
// Essentially, if the system is working correctly in the
// core and at the edges, there's (virtually) no possible
// way the intermediate section isn't behaving as expected.

void show_sample( Domain T )
{
		int x = T.settings.p_x / 2;
		int y = T.settings.p_y / 2;
		int z = T.settings.p_z / 2;
		cout <<"T["<<setw(2)<<x<<"]["<<setw(2)<<y<<"]["<<setw(2)<<z<<  "] (middle) = " << T.m[x][y][z] << endl;
		cout <<"T["<<setw(2)<<x+1<<"]["<<setw(2)<<y<<"]["<<setw(2)<<z<<"]          = " << T.m[x+1][y][z] << endl;
		cout <<"T["<<setw(2)<<x-1<<"]["<<setw(2)<<y<<"]["<<setw(2)<<z<<"]          = " << T.m[x-1][y][z] << endl;
		cout <<"T["<<setw(2)<<x<<"]["<<setw(2)<<y+1<<"]["<<setw(2)<<z<<"]          = " << T.m[x][y+1][z] << endl;
		cout <<"T["<<setw(2)<<x<<"]["<<setw(2)<<y-1<<"]["<<setw(2)<<z<<"]          = " << T.m[x][y-1][z] << endl;
		cout <<"T["<<setw(2)<<x<<"]["<<setw(2)<<y<<"]["<<setw(2)<<z+1<<"]          = " << T.m[x][y][z+1] << endl;
		cout <<"T["<<setw(2)<<x<<"]["<<setw(2)<<y<<"]["<<setw(2)<<z-1<<"]          = " << T.m[x][y][z-1] << endl;
		cout << "T[0][0][0] (boundary)  = " << T.m[0][0][0] << endl;
		cout << "T[1][1][1] (boundary+1)= " << T.m[1][1][1] << endl;
}
