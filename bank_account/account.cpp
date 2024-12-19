#include "account.h"
#include <cstdlib>
#include <iostream>


SavingsAccount::SavingsAccount(unsigned long customerID) {
    this->balance = 0.0;
    this->customerID = customerID;
}

void SavingsAccount::deposit(double amount) {

    try{
        if(amount < 0){
            throw std::invalid_argument("Amount must be positive, nothing changed.");
        }
    }catch(std::invalid_argument &e){
        std::cerr << e.what() << std::endl;
        return;
    }

    balance += amount;
}

bool SavingsAccount::withdraw(double amount) {

    try{
        if(balance < amount){
            throw std::invalid_argument("Insufficient funds, nothing changed.");
        }
    }
    catch(std::invalid_argument &e){
        std::cerr << e.what() << std::endl;
        return false;
    }

    balance -= amount;
    return true;

}

CheckingAccount::CheckingAccount(unsigned long customerID, double fee_percentage = 0.01){
    balance = 0.0;
    this->customerID = customerID;
    this->fee_percentage = fee_percentage;
}

void CheckingAccount::deposit(double amount) {

    try{
        if(amount < 0){
            throw std::invalid_argument("Amount must be positive, nothing changed.");
        }
    }catch(std::invalid_argument &e){
        std::cerr << e.what() << std::endl;
        return;
    }

    balance += amount;
}

bool CheckingAccount::withdraw(double amount) {

    amount += amount * fee_percentage;

    try{
        if(balance < amount){
            throw std::invalid_argument("Insufficient funds, nothing changed.");
        }
    }
    catch(std::invalid_argument &e){
        std::cerr << e.what() << std::endl;
        return false;
    }

    balance -= amount;
    return true;

}


std::ostream& operator<<(std::ostream &stream, const Account &account){
    stream << "Account ID: " << account.get_customerID() << " Balance: " << account.get_balance();
    return stream;
}
