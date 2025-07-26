#pragma once
#include "Headers.h"
#include "SignUp.h"
#include "HashTable.h"
#include "SplayTree.h"
#include "Movies.h"
#include "Searches.h"
#include "Avl.h"

class Menu /// Movies
{
	/*SplayTree cache;
	HashTable<string, AVLTree<pair<float, string>>> Movies;
	SearchMovie searchFunctions;*/
public:
	Menu();
	int ShowMenu();


	/*void search(size_t typeOfSearch, string movieName);
	void showSuggest();
	const Movie& findMovie(string movieName);
	void addMovie(const Movie& m);
	void deleteMovie(string movieName);*/
};
