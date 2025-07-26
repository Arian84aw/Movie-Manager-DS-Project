#pragma once
#include "Headers.h"
#include "Movies.h"
class Admin
{
public:
	void AddMovie(Movies&,string name, string genre, string story, string language, int year, string country, float score = -1);
	void AddSerial(Serials&,string name, string genre, string story, string language, int year, string country,
		float episodeTime, int seasonsNum, int episodesNum, float score = -1);
	void RemoveMovie(Movies&, string);
	void RemoveSerial(Serials&, string);
};