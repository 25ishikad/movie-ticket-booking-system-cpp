#pragma once
// 11_PriceCalculator.cpp
// ONE responsibility: turn a list of ShowSeats into a total amount. Must NOT book or pay anything.
#include <vector>
#include "06_ShowSeat.cpp"
using namespace std;

class PriceCalculator {
public:
    double calculateTotal(vector<ShowSeat*>& seats) {
        double total = 0.0;
        for (ShowSeat* s : seats) total += s->getSeat()->getPrice();
        return total;
    }
};
