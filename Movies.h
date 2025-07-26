#pragma once
#include "Headers.h"
#include "SplayTree.h"
#include "CompressedTrie.h"
#include "Avl.h"
#include "HashTable.h"
#include "Searches.h"
#include "Levenshtein.h"
#include "Sort.h"
#include "huffman tree.h"

class Movie
{
public:
	Movie() : name(""), genre(""), story(""), language(""), country(""), year(0), score(-1) {}
	Movie(string name, string ganre, string story, string language, int year,string country,float score = -1);
	void ShowMovieInfo();
	string getGenre() const;
	string getName() const;
	string getStory() const;
	string getLanguage() const;
	int getYear() const;
	float getScore() const;
	string getCountry() const;
	void setScore(float);
	bool operator==(const Movie& other) const;
	
	void operator =(const Movie& other)
	{
		this->name = other.name;
		this->country = other.country;
		this->genre = other.genre;
		this->score = other.score;
		this->year = other.year;

	}
	bool operator >(const Movie& other) const
	{
		return  this->score > other.score;
	}
	bool operator <(const Movie& other)const
	{
		return this->score < other.score;
	}
private:
	string name;
	string genre;
	string story;
	string language;
	string country;
	int year;
	float score;
	vector<float> scoreAvg;


};
const Movie NIL("", "", "", "", 0, "");


class Movies
{

public:
	Movies()
		: allMovies(),
		genres(),
		languages(),
		years(),
		countries(),
		scores() {}

	vector<Movie> getAllMovieVector();
	void BuildDecisionTree();
	void RecommendedFromDecisionTree();
	void InsertMovie(Movie&);
	void RemoveMovie(string);
	void ShowAllMovies();
	void showSuggest();
	void watch_movie(string movieName);
	const Movie& findMovie(string movieName);
	void Search(size_t typeOfSearch, string movieName);
	void Filter(string genre = "\0", string language = "\0", int year = -1, string country = "\0", float score = -1);
	vector<Movie> IntersectMovies( vector<Movie>& v1,  vector<Movie>& v2);
	bool exists(string movieName);
	void setScore(const string&, float);
	void showMoviesForDelete(string name);
	void showCompressedNameOfMovies() const;

private:

	class SearchMovie {
		HashTable<string, Movie> movies;
		CompressedTrie trie;
		SplayTree cache;
	public:

		void addNewMovieToList(Movie& m) {
			//movies[m.getName()] = m;
			movies.insert(m.getName(), m);
			//movies.push_back(m);
			trie.insert(m.getName());
		}
		
		void deleteMovie(const string& search_text) {
			if (trie.find(search_text)) {
				movies.remove(search_text, movies.get(search_text));
				trie.delete_word(search_text);
			}
			else {
				cout << "this movie doesn't exist" << endl;
				return;
			}
			if (cache.find(search_text)) {
				cache.erase(search_text);
			}
		}

		bool exists(const string& search_text) {
			return trie.find(search_text);
		}

		const Movie& find(const string& search_text) {
			if (trie.find(search_text)) {
				cache.insert(search_text);
				return movies.get(search_text); //O(1)
			}
			return NIL;
		}

		void setScores(string movie_name, float score) {
			movies.get(movie_name).setScore(score);
		}

		void showResults(const string& search_text, SplayTree& genreCache) { // normal search
			vector<string> v;
			trie.get_similar_results(search_text, v);
			for (const string& name : v) {
				cout << name << endl;
				cache.insert(name);
				genreCache.insert(movies.get(name).getGenre());
			}
			//trie.print_similar_results(search_text);
		}

		void advancedSearch(const string& search_text, SplayTree& genreCache) {
			//cout << "~ recently searched: " << endl;
			//cout << "\n~ similar results :" << endl;
			cout << "\n~ Do you mean ..." << endl;

			HashTable<string, bool> s;
			getRecentlySearches(s);
			vector<string> v;
			trie.get_similar_results(search_text, v);
			
			for (const string& name : v) {
				if (s.exists(name))
				{
					cout << name << endl;
					cache.insert(name);
					genreCache.insert(movies.get(name).getGenre());
					s.remove(name, true);
				}
			}


			vector<string> names = s.getTable();
			//vector<string> names = movies.getTable();
			Levenshtein lev;
			for (auto name : names) {
				if ((lev.minDistance(search_text, name) <= max(name.length(), search_text.length()) / 3) && (s.exists(name))) {
					cout << name << endl;
					cache.insert(name);
					genreCache.insert(movies.get(name).getGenre());
				}
			}
			cout << endl;
		}

		void showRecentlySearches() {
			cache.printNearRoot(2);
		}

		void getRecentlySearches(HashTable<string, bool>& s) {
			cache.getNearRoot(2, s);
		}

		const vector<string> AllMoviesName() const {
			return movies.getTable();
		}

		void watch_movie(const string& movie_name, SplayTree& genreCache) {
			//if (!cache.empty())
			//{
			cache.insert(movie_name);
			genreCache.insert(movies.get(movie_name).getGenre());
			movies.get(movie_name).ShowMovieInfo();
			//return;
		//}
		//cout << "Movie not found, we suggest you to search to find movie !"<<endl;
		}

		void applyLevenshtein(string _name) {
			vector<string> names = movies.getTable();
			Levenshtein lev;
			for (auto name : names) {
				if (lev.minDistance(name, _name) <= max(_name.length(), name.length()) / 3) {
					cout << name << endl;
				}
			}
		}
	};

	 SplayTree cache;
	 HashTable<string, AVLTree<pair<float, string>>> allMovies;
	 SearchMovie searchFunctions;
	 vector<Movie> allMoviesVector;
	 HashTable<string,HashTable<string,Movie>> genres;
	 HashTable<string, HashTable<string, Movie>> languages;
	 HashTable<int, HashTable<string, Movie>> years;
	 HashTable<string, HashTable<string, Movie>> countries;
	 HashTable<float, HashTable<string, Movie>> scores;

	 class DecisionTree {
	 public:
		 class Node {
		 public:
			 string question;
			 unordered_map<string, Node*> branches;
			 vector<Movie> recommendedMovies;

			 Node(string q = "") : question(q) {}
			 ~Node() {
				 for (auto& branch : branches) {
					 delete branch.second;
				 }
			 }
		 };
		 Node* root;

		 DecisionTree() : root(nullptr) {}
		 ~DecisionTree() {
			 delete root;
		 }

		 void buildTree(vector<Movie>& movies) {
			 root = buildTreeRecursive(movies, { "genre", "language", "country", "score" }, 0);
		 }

	 private:
		 Node* buildTreeRecursive(const vector<Movie>& movies, const vector<string> features, int depth) {
			 if (movies.empty() || depth >= features.size()) {
				 Node* leaf = new Node();
				 leaf->recommendedMovies = movies;
				 return leaf;
			 }

			 string currentFeature = features[depth];
			 Node* node = new Node(getQuestion(currentFeature));

			 unordered_map<string, vector<Movie>> groupedMovies;
			 for (auto& movie : movies) {
				 string key = getFeatureValue(movie, currentFeature);
				 groupedMovies[key].push_back(movie);
			 }

			 for (const auto& pair : groupedMovies) {
				 const string& key = pair.first;
				 const vector<Movie>& group = pair.second;
				 node->branches[key] = buildTreeRecursive(group, features, depth + 1);
			 }

			 return node;
		 }


		 string getQuestion(const string& feature) {
			 if (feature == "genre") return "Genre";  //What is the genre of the movie ? 
			 if (feature == "language") return "Language";     //What is the language of the movie?
			 if (feature == "country") return "Country"; //What is the country of origin?
			 if (feature == "score") return  "Score";  //Is the score greater than 8?
			 return "";
		 }

		 string getFeatureValue(const Movie& movie, const string& feature) {
			 if (feature == "genre") return movie.getGenre();
			 if (feature == "language") return movie.getLanguage();
			 if (feature == "country") return movie.getCountry();
			 if (feature == "score") return (movie.getScore() > 8) ? "Yes" : "No";
			 return "";
		 }

	 public:

		 void displayRecommendedMovies(vector<Movie>& recommendedMovies) {
			 if (recommendedMovies.empty()) {
				 cout << "No movies match your preferences." << endl;
			 }
			 else {
				 cout << "Here are your recommended movies:" << endl;
				 for (Movie& movie : recommendedMovies) {
					 movie.ShowMovieInfo();
				 }
			 }
		 }

		 void recommendMovies(Node* node, unordered_map<string, string>& userInput) {
			 if (!node) return;

			 if (node->branches.empty()) {
				 displayRecommendedMovies(node->recommendedMovies);
			 }

			 string answer = userInput[node->question];

			 if (node->branches.find(answer) != node->branches.end()) {
				 return recommendMovies(node->branches[answer], userInput);
			 }

		 }
	 };
	 DecisionTree decisionTree;

};


class Serial
{
public:
	Serial()
		: name(""), genre(""), story(""), language(""), country(""), year(0), score(-1), seasonsNum(0), episodesNum(0), episodeTime(0.0f) {}

	Serial(string name, string genre, string story, string language, int year, string country,
		float episodeTime, int seasonsNum, int episodesNum, float score = -1);
	void ShowSerialInfo()const;
	string getGenre()const;
	string getName()const;
	string getStory()const;
	string getLanguage()const;
	int getYear()const;
	float getScore()const;
	string getCountry()const;
	void setScore(float);
	void operator =(const Serial& other)
	{
		this->name = other.name;
		this->country = other.country;
		this->genre = other.genre;
		this->score = other.score;
		this->year = other.year;
	}
	bool operator==(const Serial& other) const;

	bool operator >(const Serial& other) const
	{
		return  this->score > other.score;
	}
	bool operator <(const Serial& other)const
	{
		return this->score < other.score;
	}
private:
	string name;
	string genre;
	string story;
	string language;
	string country;
	int year;
	float score;
	vector<float> scoreAvg;
	int seasonsNum;
	int episodesNum;
	float episodeTime;
};

const Serial NIL2("", "", "", "", 0, "",0,0,0);

class Serials
{
public:
	Serials()
		: allMovies(),
		genres(),
		languages(),
		years(),
		countries(),
		scores() {}
	void InsertSerial(Serial&);
	void RemoveSerial(string);
	void ShowAllSerials();
	void showSuggest();
	void watch_movie(string movieName);
	bool exists(string movieName);
	void setScore(const string&, float);
	const Serial& findSerial(string movieName);
	void showMoviesForDelete(string name);
	void Search(size_t typeOfSearch, string movieName);
	void Filter(string genre = "\0", string language = "\0", int year = -1, string country = "\0", float score = -1);
	vector<Serial> IntersectSerials(vector<Serial>& v1, vector<Serial>& v2);
private:

	class SearchSerial {
		HashTable<string, Serial> serials;
		CompressedTrie trie;
		SplayTree cache;
	public:

		void addNewMovieToList(Serial& m) {
			//movies[m.getName()] = m;
			serials.insert(m.getName(), m);
			//movies.push_back(m);
			trie.insert(m.getName());// .name() added to movie
			//cache.insert(m.Name());
		}

		void deleteMovie(const string& search_text) {
			if (trie.find(search_text)) {
				serials.remove(search_text, serials.get(search_text));
				trie.delete_word(search_text);
			}
			else {
				cout << "this movie doesn't exist" << endl;
				return;
			}
			if (cache.find(search_text)) {
				cache.erase(search_text);
			}
		}

		bool exists(const string& search_text) {
			return trie.find(search_text);
		}

		const Serial& find(const string& search_text) {
			if (trie.find(search_text)) {
				cache.insert(search_text);
				return serials.get(search_text); //O(1)
			}
			return NIL2;
		}

		void setScores(string movie_name, float score) {
			serials.get(movie_name).setScore(score);
		}

		void showResults(const string& search_text, SplayTree& genreCache) { // normal search
			vector<string> v;
			trie.get_similar_results(search_text, v);
			for (const string& name : v) {
				cout << name << endl;
				cache.insert(name);
				genreCache.insert(serials.get(name).getGenre());
			}
			//trie.print_similar_results(search_text);
		}

		void advancedSearch(const string& search_text, SplayTree& genreCache) {
			cout << "\n~ Do you mean ..." << endl;

			HashTable<string, bool> s;
			getRecentlySearches(s);
			vector<string> v;
			trie.get_similar_results(search_text, v);

			for (const string& name : v) {
				if (s.exists(name))
				{
					cout << name << endl;
					cache.insert(name);
					genreCache.insert(serials.get(name).getGenre());
					s.remove(name, true);
				}
			}

			vector<string> names = s.getTable();
			//vector<string> names = movies.getTable();
			Levenshtein lev;
			for (auto name : names) {
				if ((lev.minDistance(search_text, name) <= max(name.length(), search_text.length()) / 3) && (s.exists(name))) {
					cout << name << endl;
					cache.insert(name);
					genreCache.insert(serials.get(name).getGenre());
				}
			}
			cout << endl;
		}

		void showRecentlySearches() {
			cache.printNearRoot(2);
		}

		void watch_movie(const string& movie_name, SplayTree& genreCache) {
			cache.insert(movie_name);
			genreCache.insert(serials.get(movie_name).getGenre());
			serials.get(movie_name).ShowSerialInfo();
		}

		void applyLevenshtein(string _name) {
			vector<string> names = serials.getTable();
			Levenshtein lev;
			for (auto name : names) {
				if (lev.minDistance(_name, name) <= max(_name.length(), name.length()) / 3) {
					cout << name << endl;
				}
			}
		}

		void getRecentlySearches(HashTable<string, bool>& s) {
			cache.getNearRoot(2, s);
		}
	};

	SplayTree cache;
	HashTable<string, AVLTree<pair<float, string>>> allMovies;
	SearchSerial searchFunctions;
	vector<Serial> allMoviesVector;
	HashTable<string, HashTable<string, Serial>> genres;
	HashTable<string, HashTable<string, Serial>> languages;
	HashTable<int, HashTable<string, Serial>> years;
	HashTable<string, HashTable<string, Serial>> countries;
	HashTable<float, HashTable<string, Serial>> scores;
};