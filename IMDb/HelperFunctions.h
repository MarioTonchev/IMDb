#pragma once
#include "Movie.h";

void ClearConsole();
void ClearInputBuffer();

void SaveMovieToFile(Movie movie, const char* fileName);
void ReadMoviesFromFile(Movie movies[], int& movieCount);
void RemoveMovieFromFile(int index);
void ChangeMovieInFile(Movie movies[], int movieCnt);

void DeleteMovieFromArray(Movie movies[], int& movieCount, int index);
int FindMovieByTitle(char* title, Movie movies[], int movieCount);

bool IsLetter(char symbol);
char* ConvertWordToLower(char* word);

void PressAnyKeyToContinue();

double CalculateAverageRating(Movie movie);
char* ConvertIntArrToStrArr(int arr[], int size);
void GetRatings(char* str, Movie& movie);

int StrCmp(char* str1, char* str2);
Movie* SortByTitle(Movie movies[], int movieCnt);
Movie* SortByRating(Movie movies[], int movieCnt);