#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "HelperFunctions.h"

using namespace std;

void DisplayUserActions() {
	cout << "1. Filter movies by title" << endl;
	cout << "2. Filter movies by genre" << endl;
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

void PrintMovies(Movie movies[], int movieCnt) {
	cout << "All movies:" << endl << endl;

	for (size_t i = 0; i < movieCnt; i++)
	{
		cout << "Title: " << movies[i].title << ", Created in: " << movies[i].year
			<< ", Genre: " << movies[i].genre << ", Rating: " << movies[i].rating
			<< ", Director: " << movies[i].director << ", Actors: " << movies[i].actors << endl;
	}

	PressAnyKeyToContinue();
}

void FilterMoviesByTitle(Movie movies[], int movieCnt) {
	ClearConsole();
	cout << "Search for movies by title: ";
	char title[MAX_TITLE_LENGTH];

	ClearInputBuffer();
	cin.getline(title, MAX_TITLE_LENGTH);

	char* titleLowered = ConvertWordToLower(title);

	Movie foundMovies[MAX_MOVIES];
	int foundMoviesCnt = 0;

	for (size_t i = 0; i < movieCnt; i++)
	{
		char* searchCriteria = titleLowered;
		char* currTitle = ConvertWordToLower(movies[i].title);

		char* currTitleCopy = currTitle;

		while (*currTitleCopy != '\0')
		{
			if (*searchCriteria == *currTitleCopy)
			{
				searchCriteria++;

				if (*searchCriteria == '\0')
				{
					foundMovies[foundMoviesCnt++] = movies[i];
					break;
				}
			}
			else
			{
				searchCriteria = titleLowered;
			}

			currTitleCopy++;
		}

		delete[] currTitle;
	}

	delete[] titleLowered;

	if (foundMoviesCnt == 0)
	{
		cout << "No movies matching the title were found!" << endl;
		PressAnyKeyToContinue();
	}
	else
	{
		PrintMovies(foundMovies, foundMoviesCnt);
	}
}

void FilterMoviesByGenre(Movie movies[], int movieCnt) {
	ClearConsole();
	char genre[MAX_GENRE_LENGTH];
	cout << "Please enter genre: ";

	ClearInputBuffer();
	cin.getline(genre, MAX_GENRE_LENGTH);

	char* genreLowered = ConvertWordToLower(genre);

	Movie foundMovies[MAX_MOVIES];
	int foundMoviesCnt = 0;

	for (size_t i = 0; i < movieCnt; i++)
	{
		char* currGenreLowered = ConvertWordToLower(movies[i].genre);

		if (strcmp(currGenreLowered, genreLowered) == 0)
		{
			foundMovies[foundMoviesCnt++] = movies[i];
		}

		delete[] currGenreLowered;
	}

	delete[] genreLowered;

	if (foundMoviesCnt == 0)
	{
		cout << "No movies matching the genre were found!" << endl;
		PressAnyKeyToContinue();
	}
	else
	{
		PrintMovies(foundMovies, foundMoviesCnt);
	}
}