#include <iostream>
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

	int role;

	while (true)
	{
		cin >> role;

		if (cin.fail())
		{
			cout << "Invalid input. Please enter 1 or 2." << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
		else
		{
			if (role != 1 && role != 2)
			{
				cout << "Invalid input. Please enter 1 or 2." << endl;
			}
			else
			{
				break;
			}
		}
	}

	RunApp(movies, movieCnt, role);
}