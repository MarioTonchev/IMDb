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
void RemoveMovieFromFile(int index) {
	ifstream inputFile(MOVIES_FILE);
	ofstream tempFile(TEMP_MOVIES_FILE);

	if (!inputFile || !tempFile)
	{
		cout << "Error opening file." << endl;
		return;
	}

	char buffer[MAX_BUFFER_LENGHT];
	int currLine = 0;

	while (inputFile.getline(buffer, sizeof(buffer)))
	{
		if (currLine != index)
		{
			tempFile << buffer << endl;
		}

		currLine++;
	}

	inputFile.close();
	tempFile.close();

	remove(MOVIES_FILE);
	rename(TEMP_MOVIES_FILE, MOVIES_FILE);
}

void DeleteMovieFromArray(Movie movies[], int& movieCount, int index) {
	for (size_t i = index; i < movieCount; i++)
	{
		Movie nextMovie = movies[i + 1];

		movies[i] = nextMovie;
	}

	movieCount--;
}
int FindMovieByTitle(char* title, Movie movies[], int movieCount) {
	for (size_t i = 0; i < movieCount; i++)
	{
		char* movieTitleLowered = ConvertWordToLower(movies[i].title);

		if (strcmp(movieTitleLowered, title) == 0)
		{
			delete[] movieTitleLowered;
			return i;
		}

		delete[] movieTitleLowered;
	}

	return -1;
}

bool IsLetter(char symbol) {
	if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
	{
		return true;
	}

	return false;
}
char* ConvertWordToLower(char* word) {
	const int LETTER_DIFFERENCE = 'a' - 'A';

	char* result = new char[MAX_GENRE_LENGTH];
	int resultCnt = 0;

	char* wordCopy = word;

	while (*wordCopy != '\0')
	{
		if (IsLetter(*wordCopy) && (*wordCopy >= 'A' && *wordCopy <= 'Z'))
		{
			result[resultCnt] = *wordCopy + LETTER_DIFFERENCE;
		}
		else
		{
			result[resultCnt] = *wordCopy;
		}

		resultCnt++;
		wordCopy++;
	}

	result[resultCnt] = '\0';

	return result;
}

void PressAnyKeyToContinue() {
	cout << endl;
	cout << "Press any key to continue...";
	_getch();
	cout << endl;
}