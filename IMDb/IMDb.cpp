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
			FilterMoviesByTitle(movies, movieCnt);
			break;
		case 2:
			FilterMoviesByGenre(movies, movieCnt);
			break;
		case 3:
			ClearConsole();
			PrintMovies(movies, movieCnt);
			break;
		case 4:
			RateMovie(movies, movieCnt);
			break;
		case 5:
			ClearConsole();
			cout << "Select how do you want movies to be sorted:" << endl;
			cout << "1. By Title (In Ascending Order)" << endl;
			cout << "2. By Rating (In Ascending Order)" << endl;
			int choice;
			cin >> choice;

			if (choice == 1)
			{
				SortMoviesByTitle(movies, movieCnt);
			}
			else if (choice == 2)
			{
				SortMoviesByRating(movies, movieCnt);
			}
			break;
		case 6:
			FilterMoviesByRating(movies, movieCnt);
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
			ChangeMovieInfo(movies, movieCnt);
			break;
		case 10:		
			DeleteMovie(movies, movieCnt);
			break;
		default:
			ClearConsole();
			continue;
			break;
		}
	}
}