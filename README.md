# Next Flick: A C++ Movie Management System

**Next Flick** is a sophisticated, console-based movie and series management application developed in C++. It leverages advanced data structures to provide a rich and efficient user experience for searching, filtering, and discovering new content. The system features separate functionalities for regular users and administrators and includes several advanced search and recommendation algorithms.

This project was developed as a data structures assignment, with a key constraint of implementing all data structures and algorithms from scratch, without using standard template libraries (STL) for data structures.

---

## Core Concepts & Data Structures

The system's efficiency and advanced features are built upon a foundation of several key data structures, each serving a specific purpose:

* **`Compressed Trie`**: Used for implementing a high-speed, prefix-based search for movie and series titles. This allows users to get instant search results as they type.
* **`Splay Tree`**: Functions as a cache to optimize access to frequently or recently searched content. When a movie or genre is searched, it's brought to the root of the tree, ensuring that subsequent lookups for popular items are extremely fast. This is also used to generate recommendations based on recent search trends.
* **`Hash Table`**: Serves as the primary mechanism for filtering content. Movies and series are indexed by criteria such as **genre**, **language**, **country**, and **year** in different hash tables, allowing for rapid retrieval of filtered lists.
* **`AVL Tree`**: A self-balancing binary search tree used to maintain sorted lists. It is used to manage a user's "Favorites" list, keeping it alphabetically sorted at all times. It is also used to keep movies within a genre sorted by their rating.
* **`Levenshtein Distance`**: This algorithm is integrated into the "Advanced Search" feature to provide suggestions for misspelled queries or titles with slight variations, enhancing the search robustness.

---

## Features

The application provides a distinct set of features for two types of users: Regular Users and Admins.

### User Features

* **Sign-Up and Sign-In**: Users can create a new account or sign in to an existing one.
* **Standard Search**: Search for movies and series by typing a full or partial name, powered by the Compressed Trie.
* **Advanced Search**: For incomplete or misspelled queries, the system provides "Did you mean..." suggestions by combining results from the Splay Tree (recently searched items) and the Levenshtein distance algorithm (typographical errors).
* **Multi-Criteria Filtering**: Filter the movie/series database by genre, release year, country of origin, language, and minimum user score. Multiple filters can be applied simultaneously.
* **Watch and View Details**: Users can "watch" a movie to view its full details, including a synopsis, year, score, and more.
* **Rate Content**: Users can submit a rating (1-10) for any movie or series. The system automatically calculates and displays the average score.
* **Favorites List**: Add/remove movies and series to a personal "Favorites" list. The list can be viewed at any time and is always kept in alphabetical order.
* **Smart Recommendations**: The system suggests content based on the most recently searched genres by all users, prioritizing items with higher ratings.

### Admin Features

* **Admin Login**: A pre-defined admin account (`username: admin`, `password: admin`) provides access to administrative functions.
* **Add Movie/Series**: Admins can add new movies or series to the database by providing all relevant details (name, genre, year, summary, etc.).
* **Delete Movie/Series**: Admins can search for and completely remove a movie or series from the system. The deletion is reflected across all data structures (Trie, Splay Tree, Hash Tables) to ensure data integrity.

---

## 🌟 Bonus Features Implemented

This project implements two of the optional bonus features.

### 1. Decision Tree Recommender System

A recommendation engine built using a **Decision Tree**. The system asks the user a series of questions (e.g., preferred genre, language, country) and traverses the tree based on the answers to provide a curated list of recommended movies.

* **Usage Command**: `decision tree`

### 2. Huffman Coding for Compression

To demonstrate space optimization, movie can be compressed using a **Huffman Tree**. The algorithm calculates character frequencies across all movie titles to build an optimal prefix-code tree, which is then used to encode and decode the names.

* **Usage Command**: `show compressed`

---

## Getting Started

Follow these instructions to compile and run the project on your local machine.

### Prerequisites

* A C++ compiler that supports C++11 or newer (e.g., g++, Clang).
* A terminal or command-line interface.

### Compilation

Navigate to the project's root directory and compile the source files using the following command:

```bash
g++ main.cpp -o NextFlick
```

### Running the Application

Once compiled, run the executable:

```bash
./NextFlick
```

The application will launch, presenting you with the main menu to either sign in or sign up.

---

## Usage Guide

The application is controlled via text commands entered into the console.

### Logging In

* **User**: Choose "Sign up" to create an account or "Sign in" to log in.
* **Admin**: At the "Sign in" prompt, use the following credentials:
    * **Username**: `admin`
    * **Password**: `admin`

### Example Commands

Here are some of the commands you can use after logging in:

| Command                         | Role    | Description                                                 |
| ------------------------------- | ------- | ----------------------------------------------------------- |
| `show all movies`               | User    | Displays all movies in the database.                        |
| `search movie`                  | User    | Initiates the search functionality for movies.              |
| `filter movie`                  | User    | Starts the multi-criteria filtering process.                |
| `add movie to favorite`         | User    | Adds a movie to your personal favorites list.               |
| `show movie favorite list`      | User    | Displays your alphabetically sorted favorites.              |
| `show movie suggests`           | User    | Shows recommendations based on recent search trends.        |
| `scoreing movie`                | User    | Allows you to rate a movie.                                 |
| `decision tree`                 | User    | Starts the decision tree recommendation wizard.             |
| `Add movie`                     | Admin   | Starts the process of adding a new movie.                   |
| `Delete movie`                  | Admin   | Starts the process of deleting a movie.                     |

*(Note: Similar commands exist for serials, e.g., `search serial`, `Add serial`, etc.)*

---

## Developers

* [Arian Wahedzadegan](https://github.com/Arian84aw)
* [Pouya Pourabdollah](https://github.com/pouya-prh)

This project was completed for the Data Structures course under the supervision of Dr. Samaneh Hoseini.