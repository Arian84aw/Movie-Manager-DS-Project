#include "Headers.h"
#include "Menu.h"
#include "User.h";
#include "Admin.h"
#include "Movies.h"
using namespace std;

int main()
{
	Menu menu;
	Movies movies;
	Serials serials;
	Admin admin;


	//Movies: 
	
	// Action movies
	admin.AddMovie(movies, "Die Hard", "Action", "New York cop John McClane tries to save a building full of hostages from a group of terrorists.", "English", 1988, "USA", 8.2);
	admin.AddMovie(movies, "Mad Max: Fury Road", "Action", "In a post-apocalyptic wasteland, Max teams up with Furiosa to escape a tyrannical warlord.", "English", 2015, "Australia", 8.1);
	admin.AddMovie(movies, "John Wick", "Action", "An ex-hitman comes out of retirement to track down the men who killed his dog and took everything from him.", "English", 2014, "USA", 7.4);
	admin.AddMovie(movies, "The Avengers", "Action", "Earth's mightiest heroes must come together to stop Loki and his army from invading Earth.", "English", 2012, "USA", 8.0);
	admin.AddMovie(movies, "Gladiator", "Action", "A former Roman General sets out to exact vengeance against the corrupt emperor who murdered his family and sent him into slavery.", "English", 2000, "USA", 8.5);


	// Drama movies
	admin.AddMovie(movies, "The Shawshank Redemption", "Drama", "Two imprisoned men bond over a number of years, finding solace and eventual redemption through acts of common decency.", "English", 1994, "USA", 9.3);
	admin.AddMovie(movies, "Forrest Gump", "Drama", "The presidencies of Kennedy and Johnson, the Vietnam War, the civil rights movement and other historical events unfold from the perspective of an Alabama man with an extraordinary heart condition.", "English", 1994, "USA", 8.8);
	admin.AddMovie(movies, "The Pursuit of Happyness", "Drama", "A struggling salesman takes custody of his son as he's poised to begin a life-changing professional career.", "English", 2006, "USA", 8.0);
	admin.AddMovie(movies, "A Beautiful Mind", "Drama", "The story of John Nash, a brilliant but asocial mathematician, and his struggles with mental illness.", "English", 2001, "USA", 8.2);
	admin.AddMovie(movies, "The Godfather", "Drama", "The aging patriarch of an organized crime dynasty transfers control of his clandestine empire to his reluctant son.", "English", 1972, "USA", 9.2);


	// Crime movies
	admin.AddMovie(movies, "Pulp Fiction", "Crime", "The lives of two mob hitmen, a boxer, a gangster's wife, and a pair of diner bandits intertwine in four tales of violence and redemption.", "English", 1994, "USA", 8.9);
	admin.AddMovie(movies, "Scarface", "Crime", "In 1980 Miami, a determined Cuban immigrant takes over a drug cartel and succumbs to greed.", "English", 1983, "USA", 8.3);
	admin.AddMovie(movies, "Goodfellas", "Crime", "The story of Henry Hill and his life in the mob, covering his rise and eventual fall with the mafia.", "English", 1990, "USA", 8.7);
	admin.AddMovie(movies, "Casino", "Crime", "A Mafia associate's rise to power is followed in the 1970s Las Vegas.", "English", 1995, "USA", 8.2);
	admin.AddMovie(movies, "The Departed", "Crime", "An undercover cop and a mole in the police attempt to identify each other while infiltrating an Irish gang in South Boston.", "English", 2006, "USA", 8.5);


	// Comedy movies
	admin.AddMovie(movies, "The Hangover", "Comedy", "Three friends wake up from a bachelor party in Las Vegas with no memory of the previous night and the bachelor missing.", "English", 2009, "USA", 7.7);
	admin.AddMovie(movies, "Superbad", "Comedy", "Two high school friends aim to party before they graduate, but things go awry.", "English", 2007, "USA", 7.6);
	admin.AddMovie(movies, "Dumb and Dumber", "Comedy", "The cross-country adventures of two good-hearted but incredibly stupid friends.", "English", 1994, "USA", 7.3);
	admin.AddMovie(movies, "Anchorman", "Comedy", "In the 1970s, a San Diego news team faces competition from a female reporter.", "English", 2004, "USA", 7.2);
	admin.AddMovie(movies, "The Big Lebowski", "Comedy", "Jeff 'The Dude' Lebowski is mistaken for a wealthy man with the same name and is dragged into a kidnapping case.", "English", 1998, "USA", 8.1);


	// Other genres (Animation, Adventure, Horror, etc.)
	admin.AddMovie(movies, "The Matrix", "Sci-Fi", "A computer hacker learns from mysterious rebels about the true nature of his reality and his role in the war against its controllers.", "English", 1999, "USA", 8.7);
	admin.AddMovie(movies, "Inception", "Sci-Fi", "A thief who steals corporate secrets through the use of dream-sharing technology is given the inverse task of planting an idea into the mind of a CEO.", "English", 2010, "USA", 8.8);
	admin.AddMovie(movies, "The Lion King", "Animation", "Lion prince Simba and his father are targeted by his bitter uncle, who wants to ascend the throne himself.", "English", 1994, "USA", 8.5);
	admin.AddMovie(movies, "Avatar", "Sci-Fi", "A paraplegic Marine dispatched to the moon Pandora on a unique mission becomes torn between following his orders and protecting the world he feels is his home.", "English", 2009, "USA", 7.8);
	admin.AddMovie(movies, "Toy Story", "Animation", "A cowboy doll is profoundly threatened and jealous when a new spaceman figure supplants him as top toy in a boy's room.", "English", 1995, "USA", 8.3);

	//Serials:
	
	// Drama
	admin.AddSerial(serials, "Breaking Bad", "Drama", "A high school chemistry teacher turned methamphetamine producer navigates crime and family struggles.", "English", 2008, "USA", 47, 5, 62, 9.5);
	admin.AddSerial(serials, "The Crown", "Drama", "A chronicle of the life and reign of Queen Elizabeth II.", "English", 2016, "UK", 50, 5, 50, 8.6);
	admin.AddSerial(serials, "The Handmaid's Tale", "Drama", "In a dystopian world, a woman struggles to survive as a Handmaid in a totalitarian society.", "English", 2017, "USA", 50, 5, 56, 8.4);

	// Action
	admin.AddSerial(serials, "The Mandalorian", "Action", "A lone bounty hunter makes his way through the galaxy's outer reaches, far from the authority of the New Republic.", "English", 2019, "USA", 40, 3, 24, 8.7);
	admin.AddSerial(serials, "Vikings", "Action", "The legendary Norse hero Ragnar Lothbrok rises to power while exploring new lands and facing deadly foes.", "English", 2013, "Ireland", 45, 6, 89, 8.5);

	// Crime
	admin.AddSerial(serials, "Sherlock", "Crime", "A modern-day adaptation of Sherlock Holmes solving complex mysteries with his friend Watson.", "English", 2010, "UK", 90, 4, 13, 9.1);
	admin.AddSerial(serials, "Mindhunter", "Crime", "Two FBI agents pioneer psychological profiling techniques while delving into the minds of serial killers.", "English", 2017, "USA", 50, 2, 19, 8.6);

	// Comedy
	admin.AddSerial(serials, "Brooklyn Nine-Nine", "Comedy", "A group of detectives in the 99th precinct of the NYPD solves crimes in hilarious ways.", "English", 2013, "USA", 22, 8, 153, 8.4);
	admin.AddSerial(serials, "Parks and Recreation", "Comedy", "The absurd antics of an Indiana town's public officials as they pursue projects to make their city a better place.", "English", 2009, "USA", 22, 7, 125, 8.6);
	admin.AddSerial(serials, "Friends", "Comedy", "Follows the personal and professional lives of six friends living in New York City.", "English", 1994, "USA", 22, 10, 236, 8.9);


	while(true)
	{
		int type = menu.ShowMenu();
		if (type == 0) //user
		{
			User user;
			while (true)
			{
				string command;
				
				getline(cin, command);
				if (command == "show all movies")
				{
					user.ShowMoviesInfo(movies);
				}
				else if (command == "search movie")
				{
					user.search(movies);
				}
				else if (command == "decision tree")
				{

					movies.BuildDecisionTree();
					movies.RecommendedFromDecisionTree();
				}
				else if (command == "watch movie")
				{
					cout << "Enter movie's name :" << endl;
					string name;
					getline(cin, name);
					cin.clear();
					user.watch(movies, name);
				}
				else if (command == "filter movie")
				{
					user.Filter(movies);
				}

				else if (command == "show compressed") {
					movies.showCompressedNameOfMovies();
				}

				else if (command == "add movie to favorite")
				{
					string name;
					cout << "What is the movie`s name? ";

					getline(cin, name);
					cin.clear();
					user.InsertToFavoriteList(movies, name);
				}
				else if (command == "remove movie from favorite")
				{
					string name;
					cout << "What is the movie`s name? ";

					getline(cin, name);
					cin.clear();
					user.DeleteFromFavoriteList(movies, name);
				}
				else if (command == "show movie favorite list")
				{
					user.ShowFavoritesMovieList(movies);
				}
				else if (command == "show movie suggests")
				{
					user.PrefferdMovies(movies);
				}
				else if (command == "scoreing movie")
				{
					string name;
					float score;
					cout << "What is the movie`s name? ";
					getline(cin, name);
					cin.clear();
					cout << "score: ";
					cin >> score;
					user.Scoring(movies, name, score);
				}
				else if (command == "show all serials")
				{
					user.ShowMoviesInfo(serials);
				}
				else if (command == "search serial")
				{
					user.search(serials);
				}
				else if (command == "watch serial")
				{
					cout << "Enter serial's name :" << endl;
					string name;
					getline(cin, name);
					cin.clear();
					user.watch(serials, name);
				}
				else if (command == "filter serial")
				{
					user.Filter(serials);
				}
				else if (command == "add serial to favorite")
				{
					string name;
					cout << "What is the serial`s name? ";

					getline(cin, name);
					cin.clear();
					user.InsertToFavoriteList(serials, name);
				}
				else if (command == "remove serial from favorite")
				{
					string name;
					cout << "What is the serial`s name? ";

					getline(cin, name);
					cin.clear();
					user.DeleteFromFavoriteList(serials, name);
				}
				else if (command == "show serial favorite list")
				{
					user.ShowFavoritesSerialList(serials);
				}
				else if (command == "show serial suggests")
				{
					user.PrefferdMovies(serials);
				}
				else if (command == "scoreing serial")
				{
					string name;
					float score;
					cout << "What is the serial`s name? ";
					getline(cin, name);
					cin.clear();
					cout << "score: ";
					cin >> score;
					user.Scoring(serials, name, score);
				}
				else if (command == "exit")
				{
					break;
				}
				cin.clear();
			}

		}
		else if (type == 1) //admin
		{
			Admin admin;
			while (true)
			{
				string command;
				getline(cin, command);
				if (command == "Add movie")
				{
					string genre;
					string name;
					string country;
					string language;
					string story;
					int year;
					float score;
					cout << "Please complete the following questions:\n";

					cout << "Name: ";

					getline(cin, name);
					cin.clear();
					if (movies.exists(name)) {
						cout << "this name exists before !\n" << endl;
						continue;
					}

					cout << "Genre: ";
					getline(cin, genre);
					cin.clear();

					cout << "Country: ";
					getline(cin, country);
					cin.clear();

					cout << "Language: ";
					getline(cin, language);
					cin.clear();

					cout << "Story (brief description): ";
					getline(cin, story);
					cin.clear();

					cout << "Year: ";
					cin >> year;

					cout << "Score (out of 10): ";/// remove it later
					cin >> score;

					admin.AddMovie(movies, name, genre, story, language, year, country, score);

					cout << "Movie added successfully!\n";
				}
				else if (command == "Delete movie")
				{
					string name;
					cout << "movie Name: ";

					getline(cin, name);
					cin.clear();
					movies.showMoviesForDelete(name);

					cout << "enter Name: ";

					getline(cin, name);
					cin.clear();
					admin.RemoveMovie(movies, name);
				}
				else if (command == "Add serial")
				{
					string genre;
					string name;
					string country;
					string language;
					string story;
					int year;
					float score;
					int seasonNum;
					int episodeNum;
					float episodTime;
					cout << "Please complete the following questions:\n";

					cout << "Name: ";

					getline(cin, name);
					cin.clear();
					if (serials.exists(name)) {
						cout << "this name exists before !\n" << endl;
						continue;
					}

					cout << "Genre: ";
					getline(cin, genre);
					cin.clear();

					cout << "Country: ";
					getline(cin, country);
					cin.clear();

					cout << "Language: ";
					getline(cin, language);
					cin.clear();

					cout << "Story (brief description): ";
					getline(cin, story);
					cin.clear();

					cout << "Year: ";
					cin >> year;
					cout << "Number of season: ";
					cin >> seasonNum;
					cout << "Number of episode: ";
					cin >> episodeNum;
					cout << "Averege of each episode time: ";
					cin >> episodTime;
					cout << "Score (out of 10): ";/// remove it later
					cin >> score;

					admin.AddSerial(serials, name, genre, story, language, year, country, episodTime, seasonNum, episodeNum, score);

					cout << "Serial added successfully!\n";
				}
				else if (command == "Delete serial")
				{
					string name;
					cout << "serial Name: ";

					getline(cin, name);
					cin.clear();
					serials.showMoviesForDelete(name);

					cout << "enter Name: ";

					getline(cin, name);
					cin.clear();
					admin.RemoveSerial(serials, name);
				}
				else if (command == "exit")
				{
					break;
				}
				cin.clear();
			}
		}
		
	}

	return 0;
}