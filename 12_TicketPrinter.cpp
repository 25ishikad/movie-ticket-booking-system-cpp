#pragma once
// 12_TicketPrinter.cpp
// ONE responsibility: format and print a ticket. Printing ONLY — must NOT book, pay, or cancel.
#include <iostream>
#include "08_Booking.cpp"
#include "05_Show.cpp"
using namespace std;

class TicketPrinter {
public:
    void printTicket(Booking* booking, Show* show) {
        cout << "\n  ================ TICKET ================\n";
        cout << "   Booking ID : " << booking->getBookingId() << endl;
        cout << "   Movie      : " << show->getMovie()->getTitle() << endl;
        cout << "   Screen     : Screen-" << show->getScreen()->getScreenNo()
             << "   " << show->getShowDateTime() << endl;
        cout << "   Seats      : ";
        auto& seats = booking->getSeats();
        for (size_t i = 0; i < seats.size(); i++) {
            cout << seats[i]->getSeat()->getSeatNo() << (i + 1 < seats.size() ? ", " : "");
        }
        cout << endl;
        cout << "   Amount     : Rs." << booking->getTotalAmount()
             << "     Status: " << booking->getStatusName() << endl;
        cout << "  =========================================\n";
    }
};
