#include "account.h"
#include <iostream>


int main( int argc, char **argv ){

    std::cout << "Creating a savings account with Customer ID 1234" << std::endl;
    SavingsAccount sa(1234);
    std::cout << "Depositing $1000" << std::endl;
    sa.deposit(1000);
    std::cout << "Withdrawing $100" << std::endl;
    sa.withdraw(100);
    std::cout << "Print account:" << std::endl;
    std::cout << sa << std::endl;

    std::cout << "Creating a checking account with Customer ID 5678 and fee percenage 0.05" << std::endl;
    CheckingAccount ca(5678, 0.05);
    std::cout << "Depositing $2000" << std::endl;
    ca.deposit(2000);
    std::cout << "Withdrawing $500" << std::endl;
    ca.withdraw(500);
    std::cout << "Print account:" << std::endl;
    std::cout << ca << std::endl;

    return 0;
}