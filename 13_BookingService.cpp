#pragma once
// 13_BookingService.cpp
// ONE responsibility: the ORCHESTRATOR — runs the booking flow end to end.
// Dependency Inversion: depends on Payment* (abstraction), never on a concrete UpiPayment/CardPayment/CashPayment.
#include <vector>
#include <string>
#include <iostream>
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
using namespace std;

class BookingService {
private:
    vector<Booking*> bookings;        // COMPOSITION — BookingService owns the Booking records it creates
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

    // helper: find the ShowSeat objects matching the seat numbers the user typed
    vector<ShowSeat*> findSeats(Show* show, vector<string>& seatNos, bool& allValid) {
        vector<ShowSeat*> result;
        allValid = true;
        for (string& no : seatNos) {
            ShowSeat* found = nullptr;
            for (ShowSeat* ss : show->getShowSeats()) {
                if (ss->getSeat()->getSeatNo() == no) { found = ss; break; }
            }
            if (found == nullptr) {
                cout << "  Error: seat " << no << " does not exist.\n";
                allValid = false;
                return result;
            }
            if (!found->isAvailable()) {
                cout << "  Error: seat " << no << " is already BOOKED. Booking rejected.\n";
                allValid = false;
                return result;
            }
            result.push_back(found);
        }
        return result;
    }

public:
    ~BookingService() { for (Booking* b : bookings) delete b; }

    // FR4, FR5, FR6, FR7 all flow through this one orchestrating method
    Booking* bookSeats(Customer* customer, Show* show, vector<string> seatNos, Payment* payment) {
        bool allValid;
        vector<ShowSeat*> chosen = findSeats(show, seatNos, allValid);
        if (!allValid) return nullptr;                 // FR4: reject, nothing changes

        double total = priceCalculator.calculateTotal(chosen);   // FR5
        Booking* booking = new Booking(chosen, total);           // «create»
        for (ShowSeat* ss : chosen) ss->book();

        bool paid = payment->pay(total);                          // FR6 (polymorphic call)
        if (!paid) {
            for (ShowSeat* ss : chosen) ss->release();            // release on failure
            booking->fail();
            delete payment;
            bookings.push_back(booking);
            return booking;
        }

        booking->setPayment(payment);
        booking->confirm();
        bookings.push_back(booking);
        ticketPrinter.printTicket(booking, show);                 // FR7
        return booking;
    }

    // FR8: cancel a booking; seats become AVAILABLE again
    bool cancelBooking(string bookingId) {
        for (Booking* b : bookings) {
            if (b->getBookingId() == bookingId) {
                if (b->getStatus() != BookingStatus::CONFIRMED) return false;
                b->cancel();
                return true;
            }
        }
        return false;
    }

    vector<Booking*>& getBookings() { return bookings; }
};
