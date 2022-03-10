// Winter'22
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <forward_list>
#include <list>
#include "movies.h"
using namespace std;


void printMovieList(set<Movie>& movieList);
void printMovieList(vector<Movie>& movieList);
bool parseLine(string &line, string &movieName, double &movieRating);

struct compOperator1{
    bool operator() (Movie m1, Movie m2) {
        if ((m1.getMovieName()).compare(m2.getMovieName()) < 0){
            return true;
        }
        return false;
    }
}comp1;

struct compOperator2{
    bool operator() (Movie m1, Movie m2) {
        if (m1.getMovieRating() > m2.getMovieRating()){
            return true;
        }
        else if (m1.getMovieRating() == m2.getMovieRating()){
            if ((m1.getMovieName()).compare(m2.getMovieName()) < 0){
                return true;
            }
        }
        return false;
    }
}comp2;

int main(int argc, char** argv){
  if(argc < 2){
    cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
    cerr << "Usage: " << argv[ 0 ] << " filename prefix1 prefix2 ... prefix n " << endl;
    exit(1);
  }
  

  ifstream movieFile (argv[1]);
 

  if (movieFile.fail()){
    cerr << "Could not open file " << argv[1];
    exit(1);
  }
  
//Create an object of a STL data-structure to store all the movies

string line, movieName;
double movieRating;
Movie m;

set<Movie> movieList;

// Read each file and store the name and rating
while (getline(movieFile, line) && parseLine(line, movieName, movieRating)){
  // Use std::string movieName and double movieRating
  // to construct your Movie objects
  m.setMovieName(movieName);
  m.setMovieRating(movieRating);

  movieList.insert(m);
}
movieFile.close();

if (argc == 2){
  printMovieList(movieList);
}

vector<Movie> prefixMovieList;
vector<Movie> bestPrefixMovieList;
vector<Movie> orderedPrefixMovieList;

int deleteIndex;
string prefix;
int index;
bool firstPass = true;

if (argc > 2){

  for (int i = 2; i < argc; i++){
    prefix = argv[i];

    for (auto const& movie : movieList) {
      if (movie.isPrefix(prefix)){
        prefixMovieList.push_back(movie);
      }
    }

    if (prefixMovieList.empty()){
      cout<<"No movies found with prefix "<<prefix<<endl<<endl;
    }
    else{
      sort(prefixMovieList.begin(), prefixMovieList.end(), comp2);
      printMovieList(prefixMovieList);
      cout << endl;
      bestPrefixMovieList.push_back(prefixMovieList.at(0));
      prefixMovieList.clear();
    }
  }
  for (auto movie: bestPrefixMovieList){
    cout << "Best movie with prefix " << prefix << " is: " << movie.getMovieName() << " with rating " << std::fixed << std::setprecision(1) << movie.getMovieRating() << endl;
    //cout << movie.getMovieRating() << endl;
  }
}

//  For each prefix,
//  Find all movies that have that prefix and store them in an appropriate data structure
//  If no movie with that prefix exists print the following message
  //cout<<"No movies found with prefix "<<"<replace with prefix>"<<endl<<endl;

//  For each prefix,
//  Print the highest rated movie with that prefix if it exists.
  
  return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/


void printMovieList(set<Movie>& movieList){
    for (auto movie: movieList){
      cout << movie.getMovieName() << ", " << std::fixed << std::setprecision(1) << movie.getMovieRating() << endl;
    }
}

void printMovieList(vector<Movie>& movieList){
    for (auto movie: movieList){
      cout << movie.getMovieName() << ", " << std::fixed << std::setprecision(1) << movie.getMovieRating() << endl;
    }
}

bool parseLine(string &line, string &movieName, double &movieRating) {
  if(line.length() <= 0) return false;
  string tempRating = "";

  bool flag = false;
  movieName = tempRating = "";
  movieRating = 0.0;
  flag = false;


  for (int i = 0; i < line.length(); i++){  
    if(flag){
      tempRating += line[i];
    }
    else if(line[i]==','&& line[0]!='"'){
      flag = true;
    }
    else {
		  if(i==0 && line[0]=='"'){
        continue;
      }
		  if(line[i]=='"'){
        i++;
        flag=true; 
        continue;
      }
		  movieName += line[i];
	  }
  }
  
  movieRating = stod(tempRating);
  return true;
}