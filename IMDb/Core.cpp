#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "HelperFunctions.h"

using namespace std;

void DisplayUserActions() {
	cout << "1. Find movie by title" << endl;
	cout << "2. Find movie by genre" << endl;
	cout << "3. View all movies" << endl;
	cout << "4. Rate movie" << endl;
	cout << "5. Sort movies by rating or title" << endl;
	cout << "6. Filter movies by rating" << endl;
	cout << "7. Quit" << endl;
}

void DisplayAdminActions() {
	DisplayUserActions();

	cout << endl;

	cout << "8. Add movie" << endl;
	cout << "9. Change movie info" << endl;
	cout << "10. Delete movie" << endl;
}