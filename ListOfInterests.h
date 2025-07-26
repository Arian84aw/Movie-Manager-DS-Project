#pragma once
#include "Movies.h"

class ListOfInterests {
	AVLTree<string> InterestList;
public:
	void insert(Movies& movies, string movie_name) { // O(log n)
		if (movies.exists(movie_name)) {
			InterestList.insert(movie_name);
		}
		else {
			cout << "this movie not found";
		}
	}

	void deleteMovie(Movies& movies, string movie_name) {
		if (movies.exists(movie_name)) {
			InterestList.deleteKey(movie_name);	//O(log n)
		}
		else {
			cout << "this movie not found";
		}
	}
	
	void insert(Serials& serials, string serial_name) { // O(log n)
		if (serials.exists(serial_name)) {
			InterestList.insert(serial_name);
		}
		else {
			cout << "this serial not found";
		}
	}

	void deleteMovie(Serials& serials, string serial_name) {
		if (serials.exists(serial_name)) {
			InterestList.deleteKey(serial_name);	//O(log n)
		}
		else {
			cout << "this serial not found";
		}
	}

	void showList(Movies& movies) { // O(n)
		vector<string> names = InterestList.inOrder();
		//updating
		string prev_name;
		for (string name : names) {
			if (!movies.exists(name))
				InterestList.deleteKey(name);
			else if (prev_name != name)
				cout << name << endl;
			prev_name = name;
		}
	}
	void showList(Serials& serials) { // O(n)
		vector<string> names = InterestList.inOrder();
		//updating
		string prev_name;
		for (string name : names) {
			if (!serials.exists(name))
				InterestList.deleteKey(name);
			else if (prev_name != name)
				cout << name << endl;
			prev_name = name;
		}
	}
};

