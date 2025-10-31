#include <iostream>
#include <string>

using namespace std;

int main(){

    int list1[4] = {10, 20, 30, 40};

    list1[0] = 20;
    list1[1] = 10;

    for (int i = 0; i < 4; i++) {
        cout << list1[i] << endl;
    }
    return 0;
}