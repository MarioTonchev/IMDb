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
* <File containing definition of the movie struct>
*
*/
#pragma once
#include "MovieConstants.h";

struct Movie {
	char title[MAX_TITLE_LENGTH];
	int year;
	char genre[MAX_GENRE_LENGTH];
	char director[MAX_DIRECTOR_LENGTH];
	char actors[MAX_ACTORS_LENGTH];

	int ratings[MAX_RATINGS_LENGTH];
	int ratingsCnt = 0;
	double averageRating = 5;
};