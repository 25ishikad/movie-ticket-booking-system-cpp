#pragma once
// 08_Booking.cpp
// ONE responsibility: booking id, which show's seats, total amount, status.
// Must NOT calculate price itself (that's PriceCalculator's job) and must NOT print tickets.
#include <string>
#include <vector>
#include "06_ShowSeat.cpp"
#include "09_Payment.cpp"
using namespace std;

enum class BookingStatus { PENDING, CONFIRMED, CANCELLED, FAILED };

class Booking {
private:
    string bookingId;
    vector<ShowSeat*> seats;   // AGGREGATION — booking references seats it does not own
    double totalAmount;
    BookingStatus status;
    Payment* payment;          // COMPOSITION — this Payment record exists only for this Booking
    static int nextBookingId;

public:
    Booking(vector<ShowSeat*> seats, double totalAmount)
        : seats(seats), totalAmount(totalAmount), status(BookingStatus::PENDING), payment(nullptr) {
        bookingId = "BK" + to_string(1000 + nextBookingId++);
    }

    ~Booking() { delete payment; }

    void setPayment(Payment* p) { payment = p; }
    void confirm()  { status = BookingStatus::CONFIRMED; }
    void fail()     { status = BookingStatus::FAILED; }
    void cancel()   {
        for (ShowSeat* s : seats) s->release();   // FR8: seats become AVAILABLE again
        status = BookingStatus::CANCELLED;
    }

    string getBookingId() const { return bookingId; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }
    vector<ShowSeat*>& getSeats() { return seats; }

    string getStatusName() const {
        switch (status) {
            case BookingStatus::PENDING:   return "PENDING";
            case BookingStatus::CONFIRMED: return "CONFIRMED";
            case BookingStatus::CANCELLED: return "CANCELLED";
            case BookingStatus::FAILED:    return "FAILED";
        }
        return "";
    }
};

int Booking::nextBookingId = 1;
