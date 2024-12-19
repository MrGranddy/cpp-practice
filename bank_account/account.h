#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>

/**
    * @brief Abstract base class representing a bank account
*/

class Account{
    public:
        // Pure virtual functions, must be implemented by derived classes
        virtual void deposit(double amount) = 0;
        virtual bool withdraw(double amount) = 0;

        // This const keyword means that the function will not modify the object
        // Virtual functions can be overridden by derived classes
        virtual double get_balance() const { return balance; }
        virtual unsigned long get_customerID() const { return customerID; }

        virtual ~Account() = default;

    protected:
        double balance;
        unsigned long customerID;
};

class SavingsAccount : public Account{
    public:
        SavingsAccount(unsigned long customerID);
        virtual void deposit(double amount) override;
        virtual bool withdraw(double amount) override;
        virtual ~SavingsAccount() = default;
};

class CheckingAccount : public Account{
    public:
        CheckingAccount(unsigned long customerID, double fee_percentage = 0.01);
        virtual void deposit(double amount) override;
        virtual bool withdraw(double amount) override;
        virtual ~CheckingAccount() = default;
    private:
        double fee_percentage;
};

std::ostream& operator<<(std::ostream &stream, const Account &account);

#endif