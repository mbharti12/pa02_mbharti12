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
    cerr << "Usage: " << argv[0] << " filename prefix1 prefix2 ... prefix n " << endl;
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

  //This while loop runs 'n' number of times (the number of movies in the given csv file)
  //The getline and parseLine functions both iterate through the respective movie titles/ratings
  //This would technically be another variable that would impact runtime complexity (however, we're counting it as a constant-time operation)
  while (getline(movieFile, line) && parseLine(line, movieName, movieRating)){
    //setMovieName and setMovieRating both count as one constant-time operation (since they both update one variable)
    m.setMovieName(movieName);
    m.setMovieRating(movieRating);

    //The time complexity for inserting into sets is log(n) in this case
    movieList.insert(m);
  }
  movieFile.close();

  //PART 1
  if (argc == 2){
    //The below print function iterates thru the entire set, which has a time complexity of n
    printMovieList(movieList);
  }

  vector<Movie> prefixMovieList;
  vector<Movie> bestPrefixMovieList;
  vector<Movie> orderedPrefixMovieList;

  int deleteIndex;
  string prefix;
  int index;
  bool firstPass = true;
  vector<string> prefixList;

  //PART 2
  if (argc > 2){
    //Outer-most loop runs 'm' number of times
    for (int i = 2; i < argc; i++){
      prefix = argv[i];
      //The push_back function is one constant-time operation 
      prefixList.push_back(prefix);

      //Below for loop iterates through the entire movieList set, which has a time complexity of 'n' (the number of movies read into the set)
      for (auto const& movie : movieList) {
        if (movie.isPrefix(prefix)){
          //1 constant-time operation (although it's only called if the if statement conditional is true)
          prefixMovieList.push_back(movie);
        }
      }

      if (prefixMovieList.empty()){
        cout<<"No movies found with prefix "<<prefix<<endl<<endl;
      }
      else{
        //The sort function has a complexity of k*log(k) for k number of movies
        sort(prefixMovieList.begin(), prefixMovieList.end(), comp2);
        //The below printMovieList function iterates through the prefixMovieList, which stores 'k' number of movies
        printMovieList(prefixMovieList);
        //1 constant time operation
        cout << endl;
        //1 constant time operation
        bestPrefixMovieList.push_back(prefixMovieList.at(0));
        //constant-time since objects were not allocated to the heap
        prefixMovieList.clear();
      }
    }
    //Loop iterates 'm' number of times
    for (int i = 0; i < prefixList.size(); i++){
      //Below line is probably multiple constant-time operations, but we'll say that it's 1
      cout << "Best movie with prefix " << prefixList.at(i) << " is: " << bestPrefixMovieList.at(i).getMovieName() << " with rating " << std::fixed << std::setprecision(1) << bestPrefixMovieList.at(i).getMovieRating() << endl;
    }
  }
  
  return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

/*
I've included comments in the above implementation of Part 2 to help describe its time complexity.

The algorithm starts with the outermost for loop, which is used to iterate through each prefix. It runs an 'm' number of times.
There are a couple of constant-time operations (storing the prefix value and appending it to the prefixMovieList vector). Then we get to another for loop, which 
iterates an 'n' number of times through the entire movieList set, which stores the movies that are read in initially. Within this loop is an if statement
and push_back function, which are each 1 constant-time operation. After the for loop, comes another if statement and its body, which we'll count as singular
constant-time operations. Next, is the body of the following else statement, which adds significant complexity to the algorithm. The sort function sorts through
the movies with the given prefix (by rating and then alphabetically if multiple movies have the same rating) and it has a linearithmic complexity (k*log(k)).
Below that is the printMovieList function, which iterates through the sorted prefixMovieList vector a 'k' number of times. Below that are a few singular
constant-time operations. However, I'm not entirely sure if the .clear() function is constant-time or O(k) since it simply stores Movie objects (not pointers
to objects that are allocated to the heap). I've assumed that it's constant-time for now.

Now that we have time complexities for each line, we can combine them to find an overall complexity of the algorithm. Let's start with the innermost line complexities.
The most significant one is k*log(k) and the others are 1, 1, n, n, 1, k, 1, 1, and k. If we add these, then we'd get 'k*log(k) + 2n + 2k + 5'. For lines within
for loops, I multiplied the line complexities by the number of iterations of the loop (since that complexity would occur in each iteration of the loop). Then
we get to the outermost for loop, which iterates an 'm' number of times (for each prefix). For the same reason I just mentioned, we would multiple the already
calculated complexities by 'm', which would get us 'm*k*log(k) + 2nm + 2km + 5m'. Then we'd add 'm' to this complexity for the for loop that prints out
the best movie for each prefix.

In the end, we'd get 'm*k*log(k) + 2nm + 2km + 6m' as the overall time complexity. Since, in the worst case, the number of movies with a given prefix is
equal to the total number of movies, the Big-O for the worst case scenario would be O(m*n*log(n)).
*/


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