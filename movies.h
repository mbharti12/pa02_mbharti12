#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
using namespace std;

class Movie{
    public:
        Movie();
        Movie(string movieName, double movieRating);
        string getMovieName() const;
        double getMovieRating() const;
        void setMovieName(string movieName);
        void setMovieRating(double movieRating);
        bool isPrefix(string prefix) const;
        bool operator<(const Movie& m) const;
        bool operator==(const Movie& m) const;
        bool operator>(const Movie& m) const;
        bool operator<(const double& movieRating) const;
        bool operator==(const double& movieRating) const;
        bool operator>(const double& movieRating) const;
        bool operator=(const Movie& m);

    private:
        string movieName;
        double movieRating;
};

#endif
