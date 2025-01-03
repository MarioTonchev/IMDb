#pragma once
#include "MovieConstants.h";

struct Movie {
	char title[MAX_TITLE_LENGTH];
	int year;
	char genre[MAX_GENRE_LENGTH];
	char director[MAX_DIRECTOR_LENGTH];
	char actors[MAX_ACTORS_LENGTH];

	double rating = 5;
};