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
using namespace std;



bool parseLine(string &line, string &movieName, double &movieRating);

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
// Read each file and store the name and rating
while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
  // Use std::string movieName and double movieRating
  // to construct your Movie objects
  // cout << movieName << " has rating " << movieRating << endl;
  // insert elements into your data structure
}

movieFile.close();

if(argc == 2){
  //print all the movies in ascending alphabetical order of movie names
  return 0;
}


//  For each prefix,
//  Find all movies that have that prefix and store them in an appropriate data structure
//  If no movie with that prefix exists print the following message
cout<<"No movies found with prefix "<<"<replace with prefix>"<<endl<<endl;

//  For each prefix,
//  Print the highest rated movie with that prefix if it exists.
cout << "Best movie with prefix "<<"<replace with prefix>"<<" is: " << "replace with moview name" <<" with rating " << std::fixed << std::setprecision(1) << "replace with movie rating"<< endl;
    


return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/



bool parseLine(string &line, string &movieName, double &movieRating) {
  if(line.length() <= 0) return false;
  string tempRating = "";

  bool flag = false;
  movieName = tempRating = "", movieRating = 0.0, flag = false;

  for (int i = 0; i < line.length(); i++){
    if(flag) tempRating += line[i];
    else if(line[i]==','&& line[0]!='"') flag = true;
    else {
		  if(i==0 && line[0]=='"') continue;
		  if(line[i]=='"'){ i++; flag=true; continue;}
		  movieName += line[i];
	  }
  }
  
  movieRating = stod(tempRating);
  return true;
}