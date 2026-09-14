#pragma once
// 03_Screen.cpp
// ONE responsibility: one auditorium — owns its seats (composition: seats die with the screen).
#include <vector>
#include "02_Seat.cpp"
using namespace std;

class Screen {
private:
    int screenNo;
    vector<Seat*> seats;      // COMPOSITION: Screen creates & owns these Seats

public:
    Screen(int screenNo) : screenNo(screenNo) {}

    ~Screen() {
        for (Seat* s : seats) delete s;   // lifetime test: seats die when screen dies
    }

    void addSeat(Seat* seat) { seats.push_back(seat); }
    int getScreenNo() const { return screenNo; }
    vector<Seat*>& getSeats() { return seats; }
};
