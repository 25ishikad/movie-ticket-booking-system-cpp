#pragma once
// 06_ShowSeat.cpp
// ONE responsibility: the status of ONE seat FOR ONE show (AVAILABLE / BOOKED).
// Why not just Seat? Seat A1 physically exists once; its booking STATUS is different per show.
#include "02_Seat.cpp"

enum class Status { AVAILABLE, BOOKED };

class ShowSeat {
private:
    Seat* seat;         // ASSOCIATION — points to the physical seat, does not own it
    Status status;

public:
    ShowSeat(Seat* seat) : seat(seat), status(Status::AVAILABLE) {}

    bool isAvailable() const { return status == Status::AVAILABLE; }

    // Encapsulation: state changes only through these methods, never set directly
    void book()    { status = Status::BOOKED; }
    void release() { status = Status::AVAILABLE; }   // FR8: cancellation

    Seat* getSeat() const { return seat; }
};
