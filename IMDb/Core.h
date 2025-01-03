#pragma once

void DisplayUserActions();
void DisplayAdminActions();

void AddMovie(Movie movies[], int& movieCount);
void DeleteMovie(Movie movies[], int& movieCount);

void PrintMovies(Movie movies[], int movieCnt);