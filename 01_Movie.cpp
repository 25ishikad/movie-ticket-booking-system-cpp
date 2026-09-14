#pragma once
// 01_Movie.cpp
// ONE responsibility: hold a movie's own identity/data. Nothing about shows, seats, or price.
#include <string>
using namespace std;

class Movie {
private:                              // Encapsulation: fields are private
    int movieId;
    string title;
    string language;
    int durationMins;

public:
    Movie(int movieId, string title, string language, int durationMins)
        : movieId(movieId), title(title), language(language), durationMins(durationMins) {}

    int getMovieId() const    { return movieId; }
    string getTitle() const   { return title; }
    string getLanguage() const{ return language; }
    int getDurationMins() const { return durationMins; }
};
