#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include "HelperFunctions.h"

using namespace std;

void DisplayUserActions() {
	cout << "0. Filter movies by title" << endl;
	cout << "1. Filter movies by genre" << endl;
	cout << "2. View all movies" << endl;
	cout << "3. Rate movie" << endl;
	cout << "4. Sort movies by rating or title" << endl;
	cout << "5. Filter movies by rating" << endl;
	cout << "6. Quit" << endl;
}
void DisplayAdminActions() {
	DisplayUserActions();

	cout << endl;

	cout << "7. Add movie" << endl;
	cout << "8. Change movie info" << endl;
	cout << "9. Delete movie" << endl;
}
void PrintMovies(Movie movies[], int movieCnt) {
	cout << "All movies:" << endl << endl;

	for (size_t i = 0; i < movieCnt; i++)
	{
		cout << "Title: " << movies[i].title << ", Created in: " << movies[i].year
			<< ", Genre: " << movies[i].genre 
			<< ", Rating: " << fixed << setprecision(2) << movies[i].averageRating
			<< ", Director: " << movies[i].director << ", Actors: " << movies[i].actors << endl;
	}

	PressAnyKeyToContinue();
}

void AddMovie(Movie movies[], int& movieCnt) {
	ClearConsole();

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

	cout << "Enter actors (separated by coma): ";
	cin.getline(newMovie.actors, MAX_ACTORS_LENGTH);

	movies[movieCnt++] = newMovie;
	SaveMovieToFile(newMovie, MOVIES_FILE);

	ClearConsole();
}
void DeleteMovie(Movie movies[], int& movieCnt) {
	ClearConsole();
	cout << "Enter title of move you wish to delete: ";
	char title[MAX_TITLE_LENGTH];

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
void ChangeMovieInfo(Movie movies[], int movieCnt) {
	ClearConsole();
	cout << "Enter the title of the movie you wish to edit: ";

	char title[MAX_TITLE_LENGTH];

	cin.getline(title, MAX_TITLE_LENGTH);

	char* titleLowered = ConvertWordToLower(title);

	int movieToEditIndex = FindMovieByTitle(titleLowered, movies, movieCnt);

	delete[] titleLowered;


	if (movieToEditIndex != -1)
	{
		Movie movieToEdit = movies[movieToEditIndex];

		cout << "Editing movie... (If you don't wish to change certain fields you can skip them)" << endl;

		cout << "Enter new title: ";
		char newTitle[MAX_TITLE_LENGTH];
		cin.getline(newTitle, MAX_TITLE_LENGTH);

		if (strcmp(newTitle, "") != 0)
		{
			strcpy(movieToEdit.title, newTitle);
		}

		cout << "Enter new movie year of creation: ";
		const int MAX_YEAR_LENGTH = 5;
		char newYear[MAX_YEAR_LENGTH];
		cin.getline(newYear, MAX_YEAR_LENGTH);

		if (strcmp(newYear, "") != 0)
		{
			int yearInt = atoi(newYear);

			while (yearInt < 0)
			{
				cout << "Please enter a valid (non-negative) year!" << endl;
				cin.getline(newYear, MAX_YEAR_LENGTH);
				yearInt = atoi(newYear);
			}

			movieToEdit.year = yearInt;
		}

		cout << "Enter new movie genre: ";
		char newGenre[MAX_GENRE_LENGTH];
		cin.getline(newGenre, MAX_GENRE_LENGTH);

		if (strcmp(newGenre, "") != 0)
		{
			strcpy(movieToEdit.genre, newGenre);
		}

		cout << "Enter new movie director: ";
		char newDirector[MAX_DIRECTOR_LENGTH];
		cin.getline(newDirector, MAX_DIRECTOR_LENGTH);

		if (strcmp(newDirector, "") != 0)
		{
			strcpy(movieToEdit.director, newDirector);
		}

		cout << "Enter new actors (seperated by coma): ";
		char newActors[MAX_ACTORS_LENGTH];
		cin.getline(newActors, MAX_ACTORS_LENGTH);

		if (strcmp(newActors, "") != 0)
		{
			strcpy(movieToEdit.actors, newActors);
		}

		movies[movieToEditIndex] = movieToEdit;

		ChangeMovieInFile(movies, movieCnt);
	}
	else
	{
		cout << "Movie with such title was not found!" << endl;
		PressAnyKeyToContinue();
	}
}

void FilterMoviesByTitle(Movie movies[], int movieCnt) {
	ClearConsole();
	cout << "Search for movies by title: ";
	char title[MAX_TITLE_LENGTH];

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

void RateMovie(Movie movies[], int movieCnt) {
	ClearConsole();
	cout << "Please enter the title of the movie you wish to rate: ";

	char title[MAX_TITLE_LENGTH];
	cin.getline(title, MAX_TITLE_LENGTH);

	char* loweredTitle = ConvertWordToLower(title);

	int index = FindMovieByTitle(loweredTitle, movies, movieCnt);

	delete[] loweredTitle;

	if (index != -1)
	{
		Movie movie = movies[index];

		if (movie.ratingsCnt == MAX_RATINGS_LENGTH)
		{
			cout << "Movie has reached maximum amounts of ratings!" << endl;
		}

		cout << "Please enter a rating between 1 and 10: ";

		double rating;
		cin >> rating;

		ClearInputBuffer();

		while (rating < 1 || rating > 10)
		{
			cout << "Rating must be between 1 and 10!" << endl;

			cin >> rating;
		}

		movie.ratings[movie.ratingsCnt++] = rating;

		movie.averageRating = CalculateAverageRating(movie);

		movies[index] = movie;

		ChangeMovieInFile(movies, movieCnt);

		cout << "Rating successfully added!" << endl;
		PressAnyKeyToContinue();
	}
	else
	{
		cout << "Movie does not exist!" << endl;
		PressAnyKeyToContinue();
	}
}
void FilterMoviesByRating(Movie movies[], int movieCnt) {
	ClearConsole();
	cout << "Please enter minimum required rating: ";

	double minRating;
	cin >> minRating;

	while (minRating < 1 || minRating > 10)
	{
		cout << "Rating must be between 1 and 10!" << endl;

		cin >> minRating;
	}

	Movie* filteredMovies = new Movie[movieCnt];
	int filteredMoviesCnt = 0;

	for (size_t i = 0; i < movieCnt; i++)
	{
		if (movies[i].averageRating >= minRating)
		{
			filteredMovies[filteredMoviesCnt++] = movies[i];
		}
	}

	if (filteredMoviesCnt == 0)
	{
		cout << "No movies with rating greater than " << minRating << " were found!" << endl;
		PressAnyKeyToContinue();
	}
	else
	{
		PrintMovies(filteredMovies, filteredMoviesCnt);
	}
}

void SortMoviesByTitle(Movie movies[], int movieCnt) {
	ClearConsole();
	Movie* sortedMovies = SortByTitle(movies, movieCnt);
	cout << "(Sorted by title) ";
	PrintMovies(sortedMovies, movieCnt);
	delete[] sortedMovies;
}
void SortMoviesByRating(Movie movies[], int movieCnt) {
	ClearConsole();
	Movie* sortedMovies = SortByRating(movies, movieCnt);
	cout << "(Sorted by rating) ";
	PrintMovies(sortedMovies, movieCnt);
	delete[] sortedMovies;
}

void RunApp(Movie movies[], int movieCnt, char role) {
	while (true)
	{
		ClearConsole();
		cout << "Choose one of the following actions:" << endl << endl;

		if (role == '1')
		{
			DisplayUserActions();
		}
		else if (role == '2')
		{
			DisplayAdminActions();
		}

		char action = _getch();

		if (role == '1')
		{
			switch (action)
			{
			case '0':
				FilterMoviesByTitle(movies, movieCnt);
				break;
			case '1':
				FilterMoviesByGenre(movies, movieCnt);
				break;
			case '2':
				ClearConsole();
				PrintMovies(movies, movieCnt);
				break;
			case '3':
				RateMovie(movies, movieCnt);
				break;
			case '4': {
				ClearConsole();
				cout << "Select how do you want movies to be sorted:" << endl;
				cout << "1. By Title (In Ascending Order)" << endl;
				cout << "2. By Rating (In Ascending Order)" << endl;
				char choice = _getch();

				if (choice == '1')
				{
					SortMoviesByTitle(movies, movieCnt);
				}
				else if (choice == '2')
				{
					SortMoviesByRating(movies, movieCnt);
				}
				break;
			}
			case '5':
				FilterMoviesByRating(movies, movieCnt);
				break;
			case '6':
				return;
				break;
			default:
				ClearConsole();
				continue;
				break;
			}
		}		
		else if (role == '2')
		{
			switch (action)
			{
			case '0':
				FilterMoviesByTitle(movies, movieCnt);
				break;
			case '1':
				FilterMoviesByGenre(movies, movieCnt);
				break;
			case '2':
				ClearConsole();
				PrintMovies(movies, movieCnt);
				break;
			case '3':
				RateMovie(movies, movieCnt);
				break;
			case '4':
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
			case '5':
				FilterMoviesByRating(movies, movieCnt);
				break;
			case '6':
				return;
				break;
			case '7':
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
			case '8':
				ChangeMovieInfo(movies, movieCnt);
				break;
			case '9':
				DeleteMovie(movies, movieCnt);
				break;
			default:
				ClearConsole();
				continue;
				break;
			}
		}		
	}
}