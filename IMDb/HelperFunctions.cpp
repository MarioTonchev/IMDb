#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <conio.h>
#include "HelperFunctions.h"
#include "Movie.h"

using namespace std;

void ClearConsole() {
	cout << "\033[;H";
	cout << "\033[J";
}

void ClearInputBuffer() {
	cin.clear();
	cin.sync();
	cin.ignore();
}