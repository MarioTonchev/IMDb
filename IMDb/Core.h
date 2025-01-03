#pragma once

void DisplayUserActions();
void DisplayAdminActions();
void PrintMovies(Movie movies[], int movieCnt);

void AddMovie(Movie movies[], int& movieCount);
void DeleteMovie(Movie movies[], int& movieCount);
void ChangeMovieInfo(Movie movies[], int movieCnt);

void FilterMoviesByTitle(Movie movies[], int movieCnt);
void FilterMoviesByGenre(Movie movies[], int movieCnt);