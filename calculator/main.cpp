#include <iostream>
#include <cstdlib>

using namespace std;

double calculate(double a, double b, char op){

    if( op == '+' )
        return a + b;

    else if( op == '-' )
        return a - b;

    else if( op == '*' )
        return a * b;

    else if( op == '/' ){
        try{
            if( b == 0)
                throw "Division by zero";
            return a / b;
        }
        catch(const char* msg){
            cerr << msg << endl;
            exit(EXIT_FAILURE);
        }
    }

    else{
        try{
            throw "Invalid operator";
        }
        catch(const char* msg){
            cerr << msg << endl;
            exit(EXIT_FAILURE);
        }
    }

}

int main() {

    double a, b;
    char op;

    while(true){
    
        cout << "Enter the operation('+', '-', '*', '/' or 'q' to exit): ";
        cin >> op;

        if( op == 'q' ){
            cout << "Thank you for choosing us! Exiting..." << endl;
            break;
        }

        cout << "Enter the operands (a b): ";
        cin >> a >> b;

        cout << "Result: " << calculate(a, b, op) << endl;
    }

    return 0;
}