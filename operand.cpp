#include <iostream>

using namespace std;

int main(){

    int a = 2;
    int b = 10;

    cout << "Add: " << a + b << endl;
    cout << "Subtract: " << a - b << endl;
    cout << "Multi: " << a * b << endl;
    cout << "Devide: " << a / b << endl;
    cout << "Modulo: " << (a % b) << endl;

    cout << (a > b) << endl;
    cout << (a < b) << endl;
    cout << (a == b) << endl;

    return 0;
}