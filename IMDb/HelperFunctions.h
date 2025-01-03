#pragma once
#include "Movie.h";

void ClearConsole();
void ClearInputBuffer();

void SaveMovieToFile(Movie movie, const char* fileName);
void ReadMoviesFromFile(Movie movies[], int& movieCount);

void PressAnyKeyToContinue();