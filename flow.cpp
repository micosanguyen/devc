#include <iostream>

using namespace std;

int main() {

    int age = 20;
    bool hasID = false;

    if (age >= 18 && hasID == true){
        cout << "You can go inside" << endl;
    } else {
        cout << "You do not have permission to go inside" << endl;
    };

}