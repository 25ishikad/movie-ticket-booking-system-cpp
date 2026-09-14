#pragma once
// 07_Customer.cpp
// ONE responsibility: identify the person making a booking.
#include <string>
using namespace std;

class Customer {
private:
    int customerId;
    string name;
    string phone;
    static int nextCustomerId;   // static member -> unique ids across all customers

public:
    Customer(string name, string phone) : name(name), phone(phone) {
        customerId = nextCustomerId++;
    }

    int getCustomerId() const { return customerId; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
};

int Customer::nextCustomerId = 1;
