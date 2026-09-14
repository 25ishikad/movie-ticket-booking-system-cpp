#pragma once
// 09_Payment.cpp
// ONE responsibility: the payment CONTRACT. Abstraction — pure virtual pay().
class Payment {
protected:
    double amount;
public:
    Payment(double amount) : amount(amount) {}
    virtual bool pay(double amount) = 0;   // pure virtual -> abstract class
    virtual ~Payment() {}
};
