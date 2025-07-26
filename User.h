#pragma once
#include "Movies.h"
#include "ListOfInterests.h"
class User
{
public:
	void ShowMoviesInfo(Movies&);
	void search(Movies&);
	void Filter(Movies&);
	void ShowFavoritesMovieList(Movies& movies);
	void InsertToFavoriteList(Movies&,string);
	void DeleteFromFavoriteList(Movies&,string);
	void PrefferdMovies(Movies&);
	void Scoring(Movies&, string,float);
	void ShowMoviesInfo(Serials&);
	void search(Serials&);
	void Filter(Serials&);
	void ShowFavoritesSerialList(Serials&);
	void InsertToFavoriteList(Serials&, string);
	void DeleteFromFavoriteList(Serials&, string);
	void PrefferdMovies(Serials&);
	void Scoring(Serials&, string, float);
	void watch(Movies&, string);
	void watch(Serials&, string);
private:

	ListOfInterests interestedMovieList;
	ListOfInterests interestedSerialList;
	
	
};

