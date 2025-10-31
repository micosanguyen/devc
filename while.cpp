#include <iostream>
#include <string>

using namespace std;

int main(){

    string name;

    while (name.empty())
    {
        cout << "Enter your name: ";
        getline(cin, name);
    }
    cout << "Your name is: " << name << endl;
}