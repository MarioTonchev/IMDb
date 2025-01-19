/*
*
* Solution to course project # 6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Mario Tonchev
* @idnumber 0MI0600460
* @compiler VC
*
* <File with definitions of app core functions>
*
*/
#pragma once
#include "Movie.h";

void DisplayUserActions();
void DisplayAdminActions();
void PrintMovies(Movie movies[], int movieCnt);

void AddMovie(Movie movies[], int& movieCount);
void DeleteMovie(Movie movies[], int& movieCount);
void ChangeMovieInfo(Movie movies[], int movieCnt);

void FilterMoviesByTitle(Movie movies[], int movieCnt);
void FilterMoviesByGenre(Movie movies[], int movieCnt);

void RateMovie(Movie movies[], int movieCnt);
void FilterMoviesByRating(Movie movies[], int movieCnt);

void SortMoviesByTitle(Movie movies[], int movieCnt);
void SortMoviesByRating(Movie movies[], int movieCnt);

void RunApp(Movie movies[], int movieCnt, int role);