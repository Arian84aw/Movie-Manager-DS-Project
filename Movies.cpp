#include "Movies.h"


int getMaxScore(vector<Movie>&);
void countingSort(vector<Movie>&, int);
void radixSort(vector<Movie>&);

int getMaxScore(vector<Serial>&);
void countingSort(vector<Serial>&, int);
void radixSort(vector<Serial>&);




Movie::Movie(string name, string ganre, string story, string language, int year, string country,float score)
{
	this->name = name;
	this->genre = ganre;
	this->story = story;
	this->language = language;
	this->year = year;
	this->country = country;
	this->score = score;
	if (score >= 0)
	{
		scoreAvg.push_back(score);
	}
}

void Movie::ShowMovieInfo()
{
	cout << "name: " << name << endl << "genre: " << genre << endl << "story: " <<story<< endl
		<< "country: " << country << endl << "year: " << year <<endl << "language: " << language << endl<<"score: "<<score <<endl << "-----------------------------\n";
}

string Movie::getGenre() const
{
	return genre;
}

string Movie::getName()const
{
	return name;
}

string Movie::getStory()const
{
	return story;
}

int Movie::getYear()const
{
	return year;
}

float Movie::getScore()const
{
	return score;
}

string Movie::getCountry()const
{
	return country;
}

void Movie::setScore(float score)
{
	scoreAvg.push_back(score);
	float avg = 0;
	for (int i = 0; i < scoreAvg.size(); i++)
	{
		avg += scoreAvg[i];
	}
	this->score = std::round((avg / scoreAvg.size()) * 10.0) / 10.0;

}

string Movie::getLanguage()const
{
	return language;
}


bool Movie::operator==(const Movie& other) const {
	return name == other.name &&
		genre == other.genre &&
		country == other.country &&
		score == other.score &&
		year == other.year;
}

Serial::Serial(string name, string ganre, string story, string language, int year, 
	string country, float episodeTime, int seasonsNum, int episodesNum, float score)
{
	this->name = name;
	this->genre = ganre;
	this->story = story;
	this->language = language;
	this->year = year;
	this->country = country;
	this->score = score;
	this->episodesNum = episodesNum;
	this->episodeTime = episodeTime;
	this->seasonsNum = seasonsNum;
}

void Serial::ShowSerialInfo() const
{
	cout << "name: " << name << endl << "genre: " << genre << endl << "story: " << story << endl
		<< "country: " << country << endl << "year: " << year << endl << "language: " << language << endl
		<< "seasonNum: " << seasonsNum << endl<<"episodeNum: "<<episodesNum<<endl << "episodeTime: " << episodeTime << endl<<"-------------------------------"<<endl;
}

string Serial::getGenre()const
{
	return genre;
}

string Serial::getName()const
{
	return name;
}

string Serial::getStory()const
{
	return story;
}

string Serial::getLanguage() const
{
	return language;
}

int Serial::getYear() const
{
	return year;
}

float Serial::getScore() const
{
	return score;
}

string Serial::getCountry()const
{
	return country;
}

void Serial::setScore(float score)
{
	scoreAvg.push_back(score);
	float avg = 0;
	for (int i = 0; i < scoreAvg.size(); i++)
	{
		avg += scoreAvg[i];
	}
	this->score = std::round((avg / scoreAvg.size()) * 10.0) / 10.0;

}

bool Serial::operator==(const Serial& other) const {
	return name == other.name &&
		genre == other.genre &&
		country == other.country &&
		score == other.score &&
		year == other.year;
}


vector<Movie> Movies::getAllMovieVector()
{
	return allMoviesVector;
}

void Movies::BuildDecisionTree()
{
	vector<Movie> v = allMoviesVector;
	decisionTree.buildTree(v);
}

void Movies::RecommendedFromDecisionTree()
{
	unordered_map<string, string> userInput;

	// Ask the user for preferences
	cout << "What genre do you prefer? (Action, Drama, Sci-Fi, Comedy, etc.): ";
	string genreAnswer;
	getline(cin, genreAnswer);
	userInput["Genre"] = genreAnswer;

	cout << "What language do you prefer? (English, French, Korean, etc.): ";
	string languageAnswer;
	getline(cin, languageAnswer);
	userInput["Language"] = languageAnswer;

	cout << "What country do you prefer? (USA, France, etc.): ";
	string countryAnswer;
	getline(cin, countryAnswer);
	userInput["Country"] = countryAnswer;

	cout << "What score range do you prefer? (Yes, NO): ";
	string scoreAnswer;
	getline(cin, scoreAnswer);
	userInput["Score"] = scoreAnswer;
	decisionTree.recommendMovies(decisionTree.root, userInput);
}

void Movies::InsertMovie(Movie& movie)
{
	if (searchFunctions.exists(movie.getName())) {
		cout << "this movie exists before !" << endl;
		return;
	}

	allMoviesVector.push_back(movie);

	if (!allMovies.exists(movie.getGenre())) {
		AVLTree <pair< float, string >> newAvl;
		allMovies.insert(movie.getGenre(), newAvl);
	}
	allMovies.get(movie.getGenre()).insert({ movie.getScore(), movie.getName() });
	searchFunctions.addNewMovieToList(movie);

	string genre = movie.getGenre();
	string language = movie.getLanguage();
	string country = movie.getCountry();
	float score = movie.getScore();
	int year = movie.getYear();
	string name = movie.getName();

	if (!genres.exists(genre)) {
		genres.insert(genre, HashTable<string, Movie>());
	}
	genres.get(genre).insert(name, movie);

	if (!languages.exists(language)) {
		languages.insert(language, HashTable<string, Movie>());
	}
	languages.get(language).insert(name, movie);

	if (!countries.exists(country)) {
		countries.insert(country, HashTable<string, Movie>());
	}
	countries.get(country).insert(name, movie);

	if (!scores.exists(score)) {
		scores.insert(score, HashTable<string, Movie>());
	}
	scores.get(score).insert(name, movie);

	if (!years.exists(year)) {
		years.insert(year, HashTable<string, Movie>());
	}
	years.get(year).insert(name, movie);
}

void Movies::RemoveMovie(string name) {

	if (!searchFunctions.exists(name)) {
		cout << "this movie doesn't exist";
		return;
	}
	Movie movie = searchFunctions.find(name);
	string language = movie.getLanguage();
	string country = movie.getCountry();
	int year = movie.getYear();
	string genre = movie.getGenre();
	float score = movie.getScore();

	if (!(movie == NIL)) {
		searchFunctions.deleteMovie(name);
		allMovies.get(genre).deleteKey({ score, name });
		if (allMovies.get(genre).size() == 0) {
			allMovies.remove(genre, allMovies.get(genre));
			cache.erase(genre);
		}
	}


	if (genres.exists(genre)) {
		genres.get(genre).remove(name, movie);
	}
	if (countries.exists(country)) {
		countries.get(country).remove(name, movie);
	}
	if (languages.exists(language)) {
		languages.get(language).remove(name, movie);
	}
	if (scores.exists(score)) {
		scores.get(score).remove(name, movie);
	}
	if (years.exists(year)) {
		years.get(year).remove(name, movie);
	}
	auto it = std::find(allMoviesVector.begin(), allMoviesVector.end(), movie);
	if (it != allMoviesVector.end()) {
		allMoviesVector.erase(it);
	}
	cout << "Movie Deleted successfully!\n";
}


void Movies::ShowAllMovies()
{
	for (auto it : allMoviesVector)
	{
		it.ShowMovieInfo();
	}
}

void Movies::showSuggest()
{
	if (!cache.empty()) {
		string mostRecentGanre = cache.getMostRecent();
		auto res = allMovies.get(mostRecentGanre).inOrder();
		for (auto item : res) {
			cout << item.first << " : " << item.second << endl;
		}
	}
}

void Movies::watch_movie(string movieName) {
	if (searchFunctions.exists(movieName))
		searchFunctions.watch_movie(movieName, cache);
	else
		cout << "Movie not found, we suggest you to search to find movie !" << endl;
}

const Movie& Movies::findMovie(string movieName)
{
	if (!searchFunctions.exists(movieName)) {
		cout << "this movie doesn't exist";
		return NIL;
	}
	Movie m = searchFunctions.find(movieName);
	if (!cache.empty())
		cache.insert(m.getGenre());
	return m;
}


bool Movies::exists(string movieName) {
	if (!searchFunctions.exists(movieName))
		return false;

	return true;
}


void Movies::Search(size_t typeOfSearch, string movieName)
{
	switch (typeOfSearch)
	{
	case 1:
		searchFunctions.showResults(movieName, cache);
		break;
	case 2:
		searchFunctions.advancedSearch(movieName, cache);
		break;
	default:
		cout << "invalid input" << endl;
		break;
	}
}


void Movies::setScore(const string& movieName, float score) {
	float prevScore = searchFunctions.find(movieName).getScore();
	searchFunctions.setScores(movieName, score);
	pair<float, string> k = { prevScore, movieName };
	allMovies.get(searchFunctions.find(movieName).getGenre()).deleteKey(k);
	pair<float, string> m = { searchFunctions.find(movieName).getScore(), movieName };
	allMovies.get(searchFunctions.find(movieName).getGenre()).insert(m);
}

void Movies::showMoviesForDelete(string name) {
	searchFunctions.applyLevenshtein(name);
	cout << endl;
}

void Movies::showCompressedNameOfMovies() const{
	vector<string> words = searchFunctions.AllMoviesName();
	HuffmanTree huffman;
	auto frequencies = huffman.calculateFrequencies(words);

	HuffmanNode* huffmanTree = huffman.buildHuffmanTree(frequencies);

	unordered_map<char, string> huffmanCodes;
	huffman.generateHuffmanCodes(huffmanTree, "", huffmanCodes);

	cout << "\nHuffman Codes:\n";
	for (const auto& pair : huffmanCodes) {
		cout << pair.first << ": " << pair.second << endl;
	}

	//unordered_map<string, bitset<160>> compressedWords;
	unordered_map<bitset<256>, short int> encodedWords;

	for (const auto& word : words) {
		string encodedStr;
		for (char ch : word) {
			encodedStr += huffmanCodes[ch];
		}

		short int length = encodedStr.size();
		if (length > 256) {
			cout << "cann't compress, 256 bits doesn't enough";
			return;
		}
		bitset<256> encodedBits;
		for (size_t i = 0; i < length; ++i) {
			if (encodedStr[i] == '1') {
				encodedBits.set(i);
			}
		}

		//compressedWords[word] = encodedBits;
		encodedWords[encodedBits] = length;
	}
	for (auto pair : encodedWords) {
		string decodedWord = huffman.decodeHuffman(pair.first, pair.second, huffmanTree);

		cout << "Encoded :'" << pair.first << "' decoded to '" << decodedWord << "'" << endl;
	}
}

void Movies::Filter(string genre, string language, int year, string country, float score)
{

	bool isGenre = false;
	bool isLang = false;
	bool isYear = false;
	bool isCountry = false;
	bool isScore = false;
	if (genre == "\0" && language == "\0" && year == -1 && country == "\0" && score == -1) {
		ShowAllMovies();
	}
	if (genre != "\0")
	{
		isGenre = true;
	}
	if (language != "\0")
	{
		isLang = true;
	}
	if (year > 0)
	{
		isYear = true;
	}
	if (country != "\0")
	{
		isCountry = true;
	}
	if (score > 0)
	{
		isScore = true;
	}
	vector<Movie> byGenre;
	vector<Movie> byLanguage;
	vector<Movie> byYear;
	vector<Movie> byCountry;
	vector<Movie> byScore;
	
	
	if (genre != "\0" && genres.exists(genre)) {
		auto genreTable = genres.get(genre);
		auto genreKeys = genreTable.getTable();
		for (const auto& key : genreKeys) {
			byGenre.push_back(genreTable.get(key));
		}
		
	}

	if (language != "\0" && languages.exists(language)) {
		auto languageTable = languages.get(language);
		auto languageKeys = languageTable.getTable();
		for (const auto& key : languageKeys) {
			byLanguage.push_back(languageTable.get(key));
		}
		
	}

	if (year != -1 && years.exists(year)) {
		auto yearTable = years.get(year);
		auto yearKeys = yearTable.getTable();
		for (const auto& key : yearKeys) {
			byYear.push_back(yearTable.get(key));
		}
	
	}

	if (country != "\0" && countries.exists(country)) {
		auto countryTable = countries.get(country);
		auto countryKeys = countryTable.getTable();
		for (const auto& key : countryKeys) {
			byCountry.push_back(countryTable.get(key));
		}
		
	}

	if (score != -1) {
		for (auto it : allMoviesVector)
		{
			if (it.getScore() >= score)
			{
				byScore.push_back(it);
			}
		}
		
	}


	vector<Movie> tempResult = allMoviesVector;



	if (!byGenre.empty()||isGenre) {
		tempResult = IntersectMovies(tempResult, byGenre);
	}
	if (!byLanguage.empty()||isLang) {
		tempResult = IntersectMovies(tempResult, byLanguage);
	}
	if (!byYear.empty()||isYear) {
		tempResult = IntersectMovies(tempResult, byYear);
	}
	if (!byCountry.empty()||isCountry) {
		tempResult = IntersectMovies(tempResult, byCountry);
	}
	if (!byScore.empty()||isScore) {
		tempResult = IntersectMovies(tempResult, byScore);
	}
	
	
	radixSort(tempResult);
	for (auto it : tempResult) {
		it.ShowMovieInfo();
	}
}



vector<Movie> Movies::IntersectMovies( vector<Movie>& v1,  vector<Movie>& v2)
{
	vector<Movie> result;
	if (v1.empty() || v2.empty()) {
		//std::cout << "One of the vectors is empty." << std::endl;
		return result;
	}
	for (int i = 0; i < v1.size() ; i++)
	{

		for (int j = 0; j < v2.size(); j++) {
			if (v1[i] == v2[j]) {
				result.push_back(v2[j]);
				break;
			}
		}
	}
	return result;
}

void Serials::InsertSerial(Serial& serial)
{
	if (searchFunctions.exists(serial.getName())) {
		cout << "this serial exists before !" << endl;
		return;
	}


	allMoviesVector.push_back(serial);

	if (!allMovies.exists(serial.getGenre())) {
		AVLTree <pair< float, string >> newAvl;
		allMovies.insert(serial.getGenre(), newAvl);
	}
	allMovies.get(serial.getGenre()).insert({ serial.getScore(), serial.getName() });
	searchFunctions.addNewMovieToList(serial);

	string genre = serial.getGenre();
	string language = serial.getLanguage();
	string country = serial.getCountry();
	float score = serial.getScore();
	int year = serial.getYear();
	string name = serial.getName();

	if (!genres.exists(genre)) {
		genres.insert(genre, HashTable<string, Serial>());
	}
	genres.get(genre).insert(name, serial);

	if (!languages.exists(language)) {
		languages.insert(language, HashTable<string, Serial>());
	}
	languages.get(language).insert(name, serial);

	if (!countries.exists(country)) {
		countries.insert(country, HashTable<string, Serial>());
	}
	countries.get(country).insert(name, serial);

	if (!scores.exists(score)) {
		scores.insert(score, HashTable<string, Serial>());
	}
	scores.get(score).insert(name, serial);

	if (!years.exists(year)) {
		years.insert(year, HashTable<string, Serial>());
	}
	years.get(year).insert(name, serial);
}

void Serials::RemoveSerial(string name)
{
	if (searchFunctions.exists(name)) {
		cout << "this serial exists before !" << endl;
		return;
	}
	Serial serial = searchFunctions.find(name);
	string genre = serial.getGenre();
	string language = serial.getLanguage();
	string country = serial.getCountry();
	float score = serial.getScore();
	int year = serial.getYear();

	if (!(serial == NIL2)) {
		searchFunctions.deleteMovie(name);
		allMovies.get(genre).deleteKey({ score, name });
		if (allMovies.get(genre).size() == 0) {
			allMovies.remove(genre, allMovies.get(genre));
			cache.erase(genre);
		}
		return;
	}


	if (genres.exists(genre)) {
		genres.get(genre).remove(name, serial);
	}
	if (countries.exists(country)) {
		countries.get(country).remove(name, serial);
	}
	if (languages.exists(language)) {
		languages.get(language).remove(name, serial);
	}
	if (scores.exists(score)) {
		scores.get(score).remove(name, serial);
	}
	if (years.exists(year)) {
		years.get(year).remove(name, serial);
	}
	auto it = std::find(allMoviesVector.begin(), allMoviesVector.end(), serial);
	if (it != allMoviesVector.end()) {
		allMoviesVector.erase(it);
	}
	cout << "Serial Deleted successfully!\n";
}

void Serials::ShowAllSerials()
{
	for (auto it : allMoviesVector)
	{
		it.ShowSerialInfo();
	}
}

void Serials::showSuggest()
{
	if (!cache.empty()) {
		string mostRecentGanre = cache.getMostRecent();
		auto res = allMovies.get(mostRecentGanre).inOrder();
		for (auto item : res) {
			cout << item.first << " : " << item.second << endl;
		}
	}
}

void Serials::watch_movie(string movieName) {
	if (searchFunctions.exists(movieName))
		searchFunctions.watch_movie(movieName, cache);
	else
		cout << "Movie not found, we suggest you to search to find movie !" << endl;
}

const Serial& Serials::findSerial(string movieName)
{
	if (!searchFunctions.exists(movieName)) {
		cout << "this movie doesn't exist";
		return NIL2;
	}
	Serial m = searchFunctions.find(movieName);
	if (!cache.empty())
		cache.insert(m.getGenre());
	return m;
	/*Serial m = searchFunctions.find(movieName);
	if (!(m == NIL2)) {
		if (!cache.find(m.getGenre()))
			cache.insert(m.getGenre());

		return m;
	}
	return NIL2;*/
}

bool Serials::exists(string movieName) {
	if (!searchFunctions.exists(movieName))
		return false;

	return true;
}

void Serials::Search(size_t typeOfSearch, string movieName)
{
	switch (typeOfSearch)
	{
	case 1:
		searchFunctions.showResults(movieName, cache);
		break;
	case 2:
		searchFunctions.advancedSearch(movieName, cache);
		break;
	default:
		cout << "invalid input" << endl;
		break;
	}
}

void Serials::setScore(const string& movieName, float score) {
	float prevScore = searchFunctions.find(movieName).getScore();
	searchFunctions.setScores(movieName, score);
	pair<float, string> k = { prevScore, movieName };
	allMovies.get(searchFunctions.find(movieName).getGenre()).deleteKey(k);
	pair<float, string> m = { searchFunctions.find(movieName).getScore(), movieName };
	allMovies.get(searchFunctions.find(movieName).getGenre()).insert(m);
}

void Serials::showMoviesForDelete(string name) {
	searchFunctions.applyLevenshtein(name);
	cout << endl;
}

void Serials::Filter(string genre, string language, int year, string country, float score)
{
	if (genre == "\0" && language == "\0" && year == -1 && country == "\0" && score == -1) {
		ShowAllSerials();
	}

	vector<Serial> byGenre;
	vector<Serial> byLanguage;
	vector<Serial> byYear;
	vector<Serial> byCountry;
	vector<Serial> byScore;


	if (genre != "\0" && genres.exists(genre)) {
		auto genreTable = genres.get(genre);
		auto genreKeys = genreTable.getTable();
		for (const auto& key : genreKeys) {
			byGenre.push_back(genreTable.get(key));
		}
	}

	if (language != "\0" && languages.exists(language)) {
		auto languageTable = languages.get(language);
		auto languageKeys = languageTable.getTable();
		for (const auto& key : languageKeys) {
			byLanguage.push_back(languageTable.get(key));
		}
	}

	if (year != -1 && years.exists(year)) {
		auto yearTable = years.get(year);
		auto yearKeys = yearTable.getTable();
		for (const auto& key : yearKeys) {
			byYear.push_back(yearTable.get(key));
		}
	}

	if (country != "\0" && countries.exists(country)) {
		auto countryTable = countries.get(country);
		auto countryKeys = countryTable.getTable();
		for (const auto& key : countryKeys) {
			byCountry.push_back(countryTable.get(key));
		}
	}

	if (score != -1) {
		for (auto it : allMoviesVector)
		{
			if (it.getScore() >= score)
			{
				byScore.push_back(it);
			}
		}
	}


	vector<Serial> tempResult = allMoviesVector;

	if (!byGenre.empty()) {
		tempResult = IntersectSerials(tempResult, byGenre);
	}
	if (!byLanguage.empty()) {
		tempResult = IntersectSerials(tempResult, byLanguage);
	}
	if (!byYear.empty()) {
		tempResult = IntersectSerials(tempResult, byYear);
	}
	if (!byCountry.empty()) {
		tempResult = IntersectSerials(tempResult, byCountry);
	}
	if (!byScore.empty()) {
		tempResult = IntersectSerials(tempResult, byScore);
	}

	radixSort(tempResult);
	for (auto it : tempResult) {
		it.ShowSerialInfo();
	}
}

vector<Serial> Serials::IntersectSerials(vector<Serial>& v1, vector<Serial>& v2)
{
	vector<Serial> result;
	if (v1.empty() || v2.empty()) {
		std::cout << "One of the vectors is empty." << std::endl;
		return result;
	}
	for (int i = 0; i < v1.size(); i++)
	{

		for (int j = 0; j < v2.size(); j++) {
			if (v1[i] == v2[j]) {
				result.push_back(v2[j]);
				break;
			}
		}
	}
	return result;
}




int getMaxScore(vector<Movie>& movies) {
	int maxScore = 0;
	for (auto& movie : movies) {
		int scaledScore = static_cast<int>(movie.getScore() * 10);
		maxScore = max(maxScore, scaledScore);
	}
	return maxScore;
}


void countingSort(vector<Movie>& movies, int exp) {
	int n = movies.size();
	vector<Movie> output(n);
	int count[10] = { 0 };

	for (auto& movie : movies) {
		int scaledScore = static_cast<int>(movie.getScore() * 10);
		int digit = (scaledScore / exp) % 10;
		count[digit]++;
	}


	for (int i = 1; i < 10; ++i) {
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; --i) {
		int scaledScore = static_cast<int>(movies[i].getScore() * 10);
		int digit = (scaledScore / exp) % 10;
		output[count[digit] - 1] = movies[i];
		count[digit]--;
	}

	for (int i = 0; i < n; ++i) {
		movies[i] = output[i];
	}
}

void radixSort(vector<Movie>& movies) {

	int maxScore = getMaxScore(movies);
	for (int exp = 1; maxScore / exp > 0; exp *= 10) {
		countingSort(movies, exp);
	}
}



int getMaxScore(vector<Serial>& movies) {
	int maxScore = 0;
	for (auto& movie : movies) {
		int scaledScore = static_cast<int>(movie.getScore() * 10);
		maxScore = max(maxScore, scaledScore);
	}
	return maxScore;
}


void countingSort(vector<Serial>& movies, int exp) {
	int n = movies.size();
	vector<Serial> output(n);
	int count[10] = { 0 };

	for (auto& movie : movies) {
		int scaledScore = static_cast<int>(movie.getScore() * 10);
		int digit = (scaledScore / exp) % 10;
		count[digit]++;
	}


	for (int i = 1; i < 10; ++i) {
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; --i) {
		int scaledScore = static_cast<int>(movies[i].getScore() * 10);
		int digit = (scaledScore / exp) % 10;
		output[count[digit] - 1] = movies[i];
		count[digit]--;
	}

	for (int i = 0; i < n; ++i) {
		movies[i] = output[i];
	}
}

void radixSort(vector<Serial>& movies) {

	int maxScore = getMaxScore(movies);
	for (int exp = 1; maxScore / exp > 0; exp *= 10) {
		countingSort(movies, exp);
	}
}
