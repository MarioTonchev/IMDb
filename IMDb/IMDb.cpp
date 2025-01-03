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
	cin >> role;
	ClearInputBuffer();

	while (role != 1 && role != 2)
	{
		cout << "Please enter 1 or 2 in order to choose your role!" << endl;
		cin >> role;
	}

	while (true)
	{
		ClearConsole();
		cout << "Choose one of the following actions:" << endl << endl;

		if (role == 1)
		{
			DisplayUserActions();
		}
		else if (role == 2)
		{
			DisplayAdminActions();
		}

		int action;
		cin >> action;

		switch (action)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			return 0;
			break;
		case 8:
			if (movieCnt + 1 <= MAX_MOVIES)
			{
				AddMovie(movies, movieCnt);
			}
			else
			{
				cout << "Maximum movie count reached!" << endl;
				PressAnyKeyToContinue();
			}
			break;
		case 9:
			break;
		case 10:			
			break;
		default:
			ClearConsole();
			continue;
			break;
		}
	}
}