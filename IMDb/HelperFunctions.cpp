#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <conio.h>
#include "HelperFunctions.h"
#include "Movie.h"

using namespace std;

void ClearConsole() {
	cout << "\033[;H";
	cout << "\033[J";
}

void ClearInputBuffer() {
	cin.clear();
	cin.sync();
	cin.ignore();
}

void SaveMovieToFile(Movie movie, const char* fileName) {
	ofstream outputFile(fileName, ios::app);

	if (!outputFile)
	{
		cout << "Error: Could not open file for writing." << endl;
		return;
	}

	outputFile << movie.title << "|"
		<< movie.year << "|"
		<< movie.genre << "|"
		<< movie.rating << "|"
		<< movie.director << "|"
		<< movie.actors << "\n";

	outputFile.close();
}
void ReadMoviesFromFile(Movie movies[], int& movieCount) {
	ifstream inputFile(MOVIES_FILE);

	if (!inputFile)
	{
		cout << "Error: Could not open file for reading." << endl;
		return;
	}

	char buffer[MAX_BUFFER_LENGHT];

	while (inputFile.getline(buffer, sizeof(buffer))) {
		Movie movie;

		char* token = strtok(buffer, "|");
		if (token)
		{
			strcpy(movie.title, token);
		}

		token = strtok(nullptr, "|");
		if (token)
		{
			movie.year = atoi(token);
		}

		token = strtok(nullptr, "|");
		if (token)
		{
			strcpy(movie.genre, token);
		}

		token = strtok(nullptr, "|");
		if (token)
		{
			movie.rating = atof(token);
		}

		token = strtok(nullptr, "|");
		if (token)
		{
			strcpy(movie.director, token);
		}

		token = strtok(nullptr, "|");
		if (token)
		{
			strcpy(movie.actors, token);
		}

		movies[movieCount++] = movie;
	}

	inputFile.close();
}

void PressAnyKeyToContinue() {
	cout << endl;
	cout << "Press any key to continue...";
	_getch();
	cout << endl;
}