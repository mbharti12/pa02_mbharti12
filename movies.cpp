//BSTs are currently the most efficient data structures that we've learned about (aside from heaps, but they use a BT intuitive implementation so it doesn't matter)
//we can see if there's a way to overload the standard library BST insert operator
//More specifically I want to define what it means for a particular value to be greater than or less than another value in this case
//I'm assuming that there's a way to do this since it seems like a need for every BST problem

//we could use a priority queue, but it's not possible to print from least to greatest
//what if we can define an iterator object for the pq to do it for us (increment to larger and larger values using it++)
//this would allow us to iterate through whatever object from least to greatest
//

//check the various containers in the stl class
//if there are none that store elements in sequential order, then look for 'sort' or other similar functions
//one possibility is using a vector, inserting all of the elements, and then using the sort function to sort it in alphabetical order
#include "movies.h"
#include <iostream>
using namespace std;

Movie::Movie(){
    this->movieName = "";
    this->movieRating = 0.0;
}

Movie::Movie(string movieName, double movieRating){
    this->movieName = movieName;
    this->movieRating = movieRating;
}

string Movie::getMovieName() const{
    return movieName;
}

double Movie::getMovieRating() const{
    return movieRating;
}

void Movie::setMovieName(string movieName){
    this->movieName = movieName;
}

void Movie::setMovieRating(double movieRating){
    this->movieRating = movieRating;
}

bool Movie::operator<(const Movie& m) const{
    if ((this->movieName).compare(m.movieName) < 0){
        return true;
    }
    return false;
}

bool Movie::operator==(const Movie& m) const{
    if ((this->movieName).compare(m.movieName) == 0){
        return true;
    }
    return false;
}

bool Movie::operator>(const Movie& m) const{
    if ((this->movieName).compare(m.movieName) > 0){
        return true;
    }
    return false;
}