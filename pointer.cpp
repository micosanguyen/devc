#include <iostream>

using namespace std;

int main(){

    int a = 10;
    int &b = a;

    b += 10;

    int *pointer = &a;


    cout << pointer << endl;
    cout << &a << endl;
    cout << a << endl;
    cout << b << endl;
    cout << &b << endl;

}