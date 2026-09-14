# Movie Ticket Booking System (C++) — TCS-504 System Design, Assignment 1

A menu-driven C++ console app for booking movie tickets at a single cinema, built to
demonstrate OOP + Low-Level Design + System Design concepts (encapsulation, abstraction,
inheritance, runtime polymorphism, composition, aggregation, association, SOLID).

## Features
- List movies (F1) and shows per movie (F2)
- Seat layout with AVAILABLE/BOOKED status (F3)
- Book one or more seats, rejecting already-booked seats (F4)
- Seat-type based pricing: SILVER ₹150 / GOLD ₹250 / PLATINUM ₹400 (F5)
- Pay by UPI / Card / Cash — failed payment releases seats, no confirmation (F6)
- Ticket printing with booking id, movie, screen, time, seats, amount (F7)
- Booking cancellation — seats return to AVAILABLE (F8)

## Build & Run
```
g++ -std=c++17 -o booking main.cpp
./booking
```

## File structure
One class per file, no header files, as required by the assignment:
```
01_Movie.cpp          07_Customer.cpp        11_PriceCalculator.cpp
02_Seat.cpp            08_Booking.cpp         12_TicketPrinter.cpp
03_Screen.cpp           09_Payment.cpp         13_BookingService.cpp
04_Cinema.cpp           10_PaymentTypes.cpp    main.cpp
05_Show.cpp
06_ShowSeat.cpp
```

## Design docs
See `TCS504_Assignment1_MovieTicketBooking.docx` in the parent submission for the full
requirement analysis, noun-verb table, relationship table, class diagram, sequence diagram,
and SOLID mapping.
