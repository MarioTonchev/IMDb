#include <iostream>
#include <conio.h>
#include "HelperFunctions.h"
#include "Core.h"

using namespace std;

int main()
{
	Movie movies[MAX_MOVIES];
	int movieCnt = 0;

	ReadMoviesFromFile(movies, movieCnt);
		
	cout << "Welcome to IMDb - the world's best place for everything movie related!" << endl << endl;
	cout << "Please choose your role (type 1 or 2):" << endl << "1. User" << endl << "2. Administrator" << endl;
	char role = _getch();

	while (role != '1' && role != '2')
	{
		cout << "Please enter 1 or 2 in order to choose your role!" << endl;
		role = _getch();
	}

	RunApp(movies, movieCnt, role);
}