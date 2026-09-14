// main.cpp
// The console menu + input reading only. No business logic lives here.
#include <iostream>
#include <vector>
#include <sstream>
#include "04_Cinema.cpp"
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "10_PaymentTypes.cpp"
#include "13_BookingService.cpp"
using namespace std;

vector<string> splitSeats(const string& line) {
    vector<string> out;
    stringstream ss(line);
    string tok;
    while (getline(ss, tok, ',')) {
        while (!tok.empty() && tok.front() == ' ') tok.erase(tok.begin());
        while (!tok.empty() && tok.back() == ' ') tok.pop_back();
        if (!tok.empty()) out.push_back(tok);
    }
    return out;
}

int main() {
    // ---- Seed sample data (in a real app this would come from a database) ----
    Cinema cinema("INOX Dehradun");

    Screen* screen1 = new Screen(1);
    screen1->addSeat(new Seat("A1", SeatType::SILVER));
    screen1->addSeat(new Seat("A2", SeatType::SILVER));
    screen1->addSeat(new Seat("A3", SeatType::SILVER));
    screen1->addSeat(new Seat("A4", SeatType::SILVER));
    screen1->addSeat(new Seat("B1", SeatType::GOLD));
    screen1->addSeat(new Seat("B2", SeatType::GOLD));
    screen1->addSeat(new Seat("B3", SeatType::GOLD));
    screen1->addSeat(new Seat("C1", SeatType::PLATINUM));
    screen1->addSeat(new Seat("C2", SeatType::PLATINUM));
    cinema.addScreen(screen1);

    Screen* screen2 = new Screen(2);
    screen2->addSeat(new Seat("A1", SeatType::SILVER));
    screen2->addSeat(new Seat("A2", SeatType::SILVER));
    screen2->addSeat(new Seat("B1", SeatType::GOLD));
    screen2->addSeat(new Seat("B2", SeatType::GOLD));
    cinema.addScreen(screen2);

    Movie* movie1 = new Movie(1, "3 Idiots", "Hindi", 170);
    Movie* movie2 = new Movie(2, "Interstellar", "English", 169);
    vector<Movie*> movies = { movie1, movie2 };

    Show* show1 = new Show(101, movie1, screen1, "06:00 PM");
    Show* show2 = new Show(102, movie1, screen2, "09:00 PM");
    Show* show3 = new Show(103, movie2, screen1, "07:30 PM");
    vector<Show*> shows = { show1, show2, show3 };

    BookingService bookingService;
    Customer customer("Shreya Rawat", "9999900000");   // demo customer

    int choice = -1;
    while (choice != 0) {
        cout << "\n===== MOVIE TICKET BOOKING =====\n";
        cout << "1. Movies  2. Book  3. Cancel  4. My tickets   0. Exit\nChoose: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }

        if (choice == 1) {
            // F1
            cout << "\n";
            for (size_t i = 0; i < movies.size(); i++) {
                cout << "  [" << (i + 1) << "] " << movies[i]->getTitle()
                     << "\t" << movies[i]->getLanguage()
                     << "\t" << movies[i]->getDurationMins() << " min\n";
            }
        }
        else if (choice == 2) {
            cout << "\n";
            for (size_t i = 0; i < movies.size(); i++)
                cout << "  [" << (i + 1) << "] " << movies[i]->getTitle() << "\n";
            cout << "Choose movie: ";
            int m; cin >> m;
            if (m < 1 || m > (int)movies.size()) { cout << "  Invalid movie choice.\n"; continue; }
            Movie* chosenMovie = movies[m - 1];

            // F2: list shows for the chosen movie
            vector<Show*> movieShows;
            cout << "\n";
            int idx = 1;
            for (Show* s : shows) {
                if (s->getMovie() == chosenMovie) {
                    cout << "  [" << idx << "] Screen-" << s->getScreen()->getScreenNo()
                         << "\t" << s->getShowDateTime() << "\n";
                    movieShows.push_back(s);
                    idx++;
                }
            }
            if (movieShows.empty()) { cout << "  No shows for this movie.\n"; continue; }
            cout << "Choose show: ";
            int sIdx; cin >> sIdx;
            if (sIdx < 1 || sIdx > (int)movieShows.size()) { cout << "  Invalid show choice.\n"; continue; }
            Show* chosenShow = movieShows[sIdx - 1];

            // F3
            chosenShow->printSeatLayout();

            cout << "Seats (e.g. A1,B2): ";
            cin.ignore();
            string line; getline(cin, line);
            vector<string> seatNos = splitSeats(line);
            if (seatNos.empty()) { cout << "  No seats entered.\n"; continue; }

            cout << "Pay by: 1.UPI  2.Card  3.Cash > ";
            int payChoice; cin >> payChoice;
            double dummyTotal = 0; // Payment amount is set inside bookSeats via PriceCalculator
            Payment* payment = nullptr;
            if (payChoice == 1) payment = new UpiPayment("shreya@upi", dummyTotal);
            else if (payChoice == 2) { cout << "Card no: "; string c; cin >> c; payment = new CardPayment(c, "12/28", dummyTotal); }
            else if (payChoice == 3) { cout << "Cash given: "; double cash; cin >> cash; payment = new CashPayment(cash, dummyTotal); }
            else { cout << "  Invalid payment choice.\n"; continue; }

            Booking* booking = bookingService.bookSeats(&customer, chosenShow, seatNos, payment);
            if (booking != nullptr && booking->getStatus() == BookingStatus::FAILED) {
                cout << "  Payment failed. Booking " << booking->getBookingId() << " NOT confirmed. Seats released.\n";
            }
        }
        else if (choice == 3) {
            // F8
            cout << "Booking ID to cancel: ";
            string bid; cin >> bid;
            bool ok = bookingService.cancelBooking(bid);
            cout << (ok ? "  Booking cancelled. Seats are AVAILABLE again.\n" : "  Could not cancel (not found or not confirmed).\n");
        }
        else if (choice == 4) {
            for (Booking* b : bookingService.getBookings()) {
                cout << "  " << b->getBookingId() << "  Rs." << b->getTotalAmount()
                     << "  " << b->getStatusName() << "\n";
            }
        }
        else if (choice != 0) {
            cout << "  Invalid menu choice.\n";
        }
    }

    cout << "Goodbye!\n";

    // cleanup
    for (Movie* m : movies) delete m;
    for (Show* s : shows) delete s;
    return 0;
}
