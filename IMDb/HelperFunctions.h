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