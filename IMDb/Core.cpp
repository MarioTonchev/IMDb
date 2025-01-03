#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "HelperFunctions.h"

using namespace std;

void DisplayUserActions() {
	cout << "1. Find movie by title" << endl;
	cout << "2. Find movie by genre" << endl;
	cout << "3. View all movies" << endl;
	cout << "4. Rate movie" << endl;
	cout << "5. Sort movies by rating or title" << endl;
	cout << "6. Filter movies by rating" << endl;
	cout << "7. Quit" << endl;
}

void DisplayAdminActions() {
	DisplayUserActions();

	cout << endl;

	cout << "8. Add movie" << endl;
	cout << "9. Change movie info" << endl;
	cout << "10. Delete movie" << endl;
}

void AddMovie(Movie movies[], int& movieCnt) {
	ClearConsole();
	ClearInputBuffer();

	Movie newMovie;

	cout << "Adding movie..." << endl;

	cout << "Enter movie title: ";
	cin.getline(newMovie.title, MAX_TITLE_LENGTH);

	cout << "Enter movie year of creation: ";
	cin >> newMovie.year;

	while (newMovie.year < 0)
	{
		cout << "Please enter a valid (non-negative) year!" << endl;
		cin >> newMovie.year;
	}

	ClearInputBuffer();

	cout << "Enter movie genre: ";
	cin.getline(newMovie.genre, MAX_TITLE_LENGTH);

	cout << "Enter movie director: ";
	cin.getline(newMovie.director, MAX_TITLE_LENGTH);

	cout << "Enter actors (seperated by coma): ";
	cin.getline(newMovie.actors, MAX_ACTORS_LENGTH);

	movies[movieCnt++] = newMovie;
	SaveMovieToFile(newMovie, MOVIES_FILE);

	ClearConsole();
}

void DeleteMovie(Movie movies[], int& movieCnt) {
	ClearConsole();
	cout << "Enter title of move you wish to delete: ";
	char title[MAX_TITLE_LENGTH];

	ClearInputBuffer();
	cin.getline(title, MAX_TITLE_LENGTH);

	char* titleLowered = ConvertWordToLower(title);
	int index = FindMovieByTitle(titleLowered, movies, movieCnt);

	if (index != -1)
	{
		RemoveMovieFromFile(index);
		DeleteMovieFromArray(movies, movieCnt, index);
	}
	else
	{
		cout << "Movie does not exist!" << endl;
		PressAnyKeyToContinue();
	}
}