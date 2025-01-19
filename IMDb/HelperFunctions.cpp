#include <iostream>
#include <fstream>
#include <conio.h>
#include "HelperFunctions.h"

using namespace std;

void ClearConsole()
{
	cout << "\033[;H";
	cout << "\033[J";
}
void ClearInputBuffer()
{
	cin.clear();
	cin.sync();
	cin.ignore();
}

int StrToInt(char* str)
{
	if (str == nullptr)
	{
		return 0;
	}

	int result = 0;
	int sign = 1;
	int i = 0;

	while (str[i] == ' ')
	{
		i++;
	}

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}

	while (str[i] != '\0' && IsDigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}

	return result * sign;
}
double StrToDouble(char* str)
{
	if (str == nullptr)
	{
		return 0.0;
	}

	double result = 0.0;
	int sign = 1;
	int i = 0;
	double fractionalPart = 0.0;
	double divisor = 1.0;

	while (str[i] == ' ')
	{
		i++;
	}

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}

	while (str[i] != '\0' && IsDigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}

	if (str[i] == '.')
	{
		i++;

		while (str[i] != '\0' && IsDigit(str[i])) {
			fractionalPart = fractionalPart * 10 + (str[i] - '0');
			divisor *= 10;
			i++;
		}
	}

	result += fractionalPart / divisor;

	return result * sign;
}

void StringCopy(char* destination, char* source)
{
	if (source == "")
	{
		return;
	}

	int destinationCnt = 0;

	while (*source != '\0')
	{
		destination[destinationCnt++] = *source;
		source++;
	}

	destination[destinationCnt] = '\0';
}
char* FindCharInString(const char* str, char ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
		{
			return (char*)str;
		}
		str++;
	}

	if (ch == '\0')
	{
		return (char*)str;
	}

	return nullptr;
}
char* StrTok(char* str, const char* delimiters)
{
	static char* nextToken = nullptr;

	if (str != nullptr)
	{
		nextToken = str;
	}

	if (nextToken == nullptr)
	{
		return nullptr;
	}

	char* tokenStart = nextToken;
	while (*tokenStart && FindCharInString(delimiters, *tokenStart))
	{
		++tokenStart;
	}

	if (*tokenStart == '\0')
	{
		nextToken = nullptr;
		return nullptr;
	}

	char* tokenEnd = tokenStart;
	while (*tokenEnd && !FindCharInString(delimiters, *tokenEnd))
	{
		++tokenEnd;
	}

	if (*tokenEnd != '\0')
	{
		*tokenEnd = '\0';
		nextToken = tokenEnd + 1;
	}
	else
	{
		nextToken = nullptr;
	}

	return tokenStart;
}

void SaveMovieToFile(Movie movie, const char* fileName)
{
	ofstream outputFile(fileName, ios::app);

	if (!outputFile)
	{
		cout << "Error: Could not open file for writing." << endl;
		return;
	}

	char* ratingsAsString = ConvertIntArrToStrArr(movie.ratings, movie.ratingsCnt);

	outputFile << movie.title << "|"
		<< movie.year << "|"
		<< movie.genre << "|"
		<< movie.director << "|"
		<< movie.actors << "|"
		<< movie.averageRating << "|"
		<< movie.ratingsCnt << "|"
		<< ratingsAsString << "\n";

	if (movie.ratingsCnt > 0)
	{
		delete[] ratingsAsString;
	}

	outputFile.close();
}
void ReadMoviesFromFile(Movie movies[], int& movieCount)
{
	ifstream inputFile(MOVIES_FILE);

	if (!inputFile)
	{
		cout << "Error: Could not open file for reading." << endl;
		return;
	}

	char buffer[MAX_BUFFER_LENGHT];

	while (inputFile.getline(buffer, sizeof(buffer)))
	{
		Movie movie;

		char* token = StrTok(buffer, "|");
		if (token)
		{
			StringCopy(movie.title, token);
		}

		token = StrTok(nullptr, "|");
		if (token)
		{
			movie.year = StrToInt(token);
		}

		token = StrTok(nullptr, "|");
		if (token)
		{
			StringCopy(movie.genre, token);
		}

		token = StrTok(nullptr, "|");
		if (token)
		{
			StringCopy(movie.director, token);
		}

		token = StrTok(nullptr, "|");
		if (token)
		{
			StringCopy(movie.actors, token);
		}

		token = StrTok(nullptr, "|");
		if (token)
		{
			movie.averageRating = StrToDouble(token);
		}

		token = StrTok(nullptr, "|");
		if (token)
		{
			movie.ratingsCnt = StrToInt(token);
		}

		token = StrTok(nullptr, "|");
		if (token)
		{
			GetRatings(token, movie);
		}

		movies[movieCount++] = movie;
	}

	inputFile.close();
}
void RemoveMovieFromFile(int index)
{
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
void ChangeMovieInFile(Movie movies[], int movieCnt)
{
	for (size_t i = 0; i < movieCnt; i++)
	{
		SaveMovieToFile(movies[i], TEMP_MOVIES_FILE);
	}

	remove(MOVIES_FILE);
	rename(TEMP_MOVIES_FILE, MOVIES_FILE);
}

void DeleteMovieFromArray(Movie movies[], int& movieCount, int index)
{
	for (size_t i = index; i < movieCount; i++)
	{
		Movie nextMovie = movies[i + 1];

		movies[i] = nextMovie;
	}

	movieCount--;
}
int FindMovieByTitle(char* title, Movie movies[], int movieCount)
{
	for (size_t i = 0; i < movieCount; i++)
	{
		if (StrCmp(movies[i].title, title) == 0)
		{
			return i;
		}
	}
	return -1;
}

bool IsLetter(char symbol)
{
	if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
	{
		return true;
	}

	return false;
}
char* ConvertWordToLower(char* word)
{
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
bool IsDigit(char symbol)
{
	if (symbol >= '0' && symbol <= '9')
	{
		return true;
	}

	return false;
}

void PressAnyKeyToContinue()
{
	cout << endl;
	cout << "Press any key to continue...";
	_getch();
	cout << endl;
}

double CalculateAverageRating(Movie movie)
{
	double result = 0;

	for (size_t i = 0; i < movie.ratingsCnt; i++)
	{
		result += movie.ratings[i];
	}

	result /= movie.ratingsCnt;

	return result;
}
char* ConvertIntArrToStrArr(int arr[], int size)
{
	int tensCount = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] == 10)
		{
			tensCount++;
		}
	}

	char* result = new char[size * 2 + tensCount + 1];
	int resultCnt = 0;

	const int DIFFERENCE_BETWEEN_CHAR_INT = 48;

	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] != 10)
		{
			result[resultCnt] = arr[i] + DIFFERENCE_BETWEEN_CHAR_INT;
			result[resultCnt + 1] = ' ';
			resultCnt += 2;
		}
		else
		{
			result[resultCnt] = '1';
			result[resultCnt + 1] = '0';
			result[resultCnt + 2] = ' ';
			resultCnt += 3;
		}
	}

	result[size * 2 + tensCount] = '\0';

	return result;
}
void GetRatings(char* str, Movie& movie)
{
	int cnt = 0;

	for (size_t i = 0; i < movie.ratingsCnt * 2; i += 2)
	{
		if (str[i] == '1' && str[i + 1] == '0')
		{
			movie.ratings[cnt++] = 10;
			i++;
		}
		else
		{
			movie.ratings[cnt++] = str[i] - '0';
		}
	}
}

int StrCmp(char* str1, char* str2)
{
	char* str1Lower = ConvertWordToLower(str1);
	char* str2Lower = ConvertWordToLower(str2);

	if (!str1Lower || !str2Lower)
	{
		if (str1Lower)
		{
			delete[] str1Lower;
		}
		if (str2Lower)
		{
			delete[] str2Lower;
		}
		return 0;
	}

	char* str1LowerCopy = str1Lower;
	char* str2LowerCopy = str2Lower;

	while (*str1Lower != '\0' && *str2Lower != '\0')
	{
		if (*str1Lower > *str2Lower)
		{
			delete[] str1LowerCopy;
			delete[] str2LowerCopy;
			return 1;
		}
		else if (*str1Lower < *str2Lower)
		{
			delete[] str1LowerCopy;
			delete[] str2LowerCopy;
			return -1;
		}
		str1Lower++;
		str2Lower++;
	}

	if (*str1Lower == '\0' && *str2Lower == '\0')
	{
		delete[] str1LowerCopy;
		delete[] str2LowerCopy;
		return 0;
	}
	else if (*str1Lower == '\0')
	{
		delete[] str1LowerCopy;
		delete[] str2LowerCopy;
		return -1;
	}
	else
	{
		delete[] str1LowerCopy;
		delete[] str2LowerCopy;
		return 1;
	}
}
Movie* SortByTitle(Movie movies[], int movieCnt)
{
	Movie* sortedMovies = new Movie[movieCnt];

	for (size_t i = 0; i < movieCnt; i++)
	{
		sortedMovies[i] = movies[i];
	}

	for (size_t i = 0; i < movieCnt - 1; i++)
	{
		for (size_t j = 0; j < movieCnt - i - 1; j++)
		{
			if (StrCmp(sortedMovies[j].title, sortedMovies[j + 1].title) > 0)
			{
				Movie temp = sortedMovies[j + 1];
				sortedMovies[j + 1] = sortedMovies[j];
				sortedMovies[j] = temp;
			}
		}
	}

	return sortedMovies;
}
Movie* SortByRating(Movie movies[], int movieCnt)
{
	Movie* sortedMovies = new Movie[movieCnt];

	for (size_t i = 0; i < movieCnt; i++)
	{
		sortedMovies[i] = movies[i];
	}

	for (size_t i = 0; i < movieCnt - 1; i++)
	{
		for (size_t j = 0; j < movieCnt - i - 1; j++)
		{
			if (sortedMovies[j].averageRating > sortedMovies[j + 1].averageRating)
			{
				Movie temp = sortedMovies[j + 1];
				sortedMovies[j + 1] = sortedMovies[j];
				sortedMovies[j] = temp;
			}
		}
	}

	return sortedMovies;
}