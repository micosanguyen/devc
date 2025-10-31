#include <iostream>

using namespace std;

int main(){

    int a = 10;
    int b = 12;
    char op;

    cout << "Please enter (+ - * /) for calculate: ";
    cin >> op;

    switch (op)
    {
    case '*': cout << "Result: " << (a * b); break;
    case '+': cout << "Result: " << (a + b); break;
    case '-': cout << "Result: " << (a - b); break;
    case '/': cout << "Result: " << (a / b); break;

    default: cout << "Please enter a valid operand";
        break;
    }

}