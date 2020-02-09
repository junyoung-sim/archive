
#include <iostream>
#include <Windows.h>
#include "pathfinder_algorithm.hpp"

using namespace std;

int main()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	Pos start, end;
	start.x = 2, start.y = 3;
	end.x = 7, end.y = 4;

	Pathfinder finder(console, 8, 10, 10, start, end, 10, 3);
	finder.pathfinding();



	system("pause");
	return 0;
}
