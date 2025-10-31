#include <iostream>

using namespace std;

int main(){
    int a = 10;
    int &ref = a;

    cout << ref << endl;

    ref += 5;

    cout << ref << endl;

    return 0;
}