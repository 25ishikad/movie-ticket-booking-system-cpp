#pragma once
// 10_PaymentTypes.cpp
// Inheritance + Runtime polymorphism: each subclass implements pay() its own way.
#include <string>
#include <iostream>
#include "09_Payment.cpp"
using namespace std;

class UpiPayment : public Payment {
private:
    string upiId;
public:
    UpiPayment(string upiId, double amount) : Payment(amount), upiId(upiId) {}
    bool pay(double amt) override {
        cout << "  [UPI] Rs." << amt << " paid successfully via " << upiId << endl;
        return true;   // demo: UPI always succeeds
    }
};

class CardPayment : public Payment {
private:
    string cardNo;
    string expiry;
public:
    CardPayment(string cardNo, string expiry, double amount)
        : Payment(amount), cardNo(cardNo), expiry(expiry) {}
    bool pay(double amt) override {
        // simple demo rule: card ending in 0000 simulates a decline (edge case: failed payment)
        if (cardNo.size() >= 4 && cardNo.substr(cardNo.size() - 4) == "0000") {
            cout << "  [CARD] Payment DECLINED for Rs." << amt << endl;
            return false;
        }
        cout << "  [CARD] Rs." << amt << " paid successfully" << endl;
        return true;
    }
};

class CashPayment : public Payment {
private:
    double receivedAmount;
public:
    CashPayment(double receivedAmount, double amount) : Payment(amount), receivedAmount(receivedAmount) {}
    bool pay(double amt) override {
        if (receivedAmount < amt) {
            cout << "  [CASH] Insufficient cash. Payment FAILED." << endl;
            return false;
        }
        cout << "  [CASH] Rs." << amt << " paid successfully" << endl;
        return true;
    }
};
