#pragma once
// 02_Seat.cpp
// ONE responsibility: one physical seat (its number + type). Knows nothing about bookings.
#include <string>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };

// Compile-time constants instead of magic numbers (clean-code checklist)
const double SILVER_PRICE   = 150.0;
const double GOLD_PRICE     = 250.0;
const double PLATINUM_PRICE = 400.0;

class Seat {
private:
    string seatNo;      // e.g. "A1"
    SeatType type;

public:
    Seat(string seatNo, SeatType type) : seatNo(seatNo), type(type) {}

    string getSeatNo() const { return seatNo; }
    SeatType getType() const { return type; }

    double getPrice() const {
        switch (type) {
            case SeatType::SILVER:   return SILVER_PRICE;
            case SeatType::GOLD:     return GOLD_PRICE;
            case SeatType::PLATINUM: return PLATINUM_PRICE;
        }
        return 0.0;
    }

    string getTypeName() const {
        switch (type) {
            case SeatType::SILVER:   return "SILVER";
            case SeatType::GOLD:     return "GOLD";
            case SeatType::PLATINUM: return "PLATINUM";
        }
        return "";
    }
};
