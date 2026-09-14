#pragma once
// 05_Show.cpp
// ONE responsibility: a Movie playing on a Screen at a time; owns its ShowSeats.
// AGGREGATION with Movie & Screen (they outlive the Show). COMPOSITION with ShowSeat.
#include <vector>
#include <string>
#include <iostream>
#include "01_Movie.cpp"
#include "03_Screen.cpp"
#include "06_ShowSeat.cpp"
using namespace std;

class Show {
private:
    int showId;
    Movie* movie;              // AGGREGATION — Show borrows the Movie, does not own it
    Screen* screen;            // AGGREGATION — Show borrows the Screen, does not own it
    string showDateTime;
    vector<ShowSeat*> showSeats; // COMPOSITION — created fresh for this show, dies with it

public:
    Show(int showId, Movie* movie, Screen* screen, string showDateTime)
        : showId(showId), movie(movie), screen(screen), showDateTime(showDateTime) {
        for (Seat* seat : screen->getSeats()) {
            showSeats.push_back(new ShowSeat(seat));   // ownership created here
        }
    }

    ~Show() {
        for (ShowSeat* ss : showSeats) delete ss;
    }

    int getShowId() const { return showId; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getShowDateTime() const { return showDateTime; }
    vector<ShowSeat*>& getShowSeats() { return showSeats; }

    // FR3: display seat layout with AVAILABLE / BOOKED status
    void printSeatLayout() const {
        cout << "\n  " << screen->getScreenNo() << "  " << showDateTime
             << " | " << movie->getTitle() << endl;
        for (ShowSeat* ss : showSeats) {
            cout << "   " << ss->getSeat()->getSeatNo()
                 << (ss->isAvailable() ? "[ ]" : "[X]") << " ";
        }
        cout << "\n  ( [ ] = available   [X] = booked )\n";
    }
};
