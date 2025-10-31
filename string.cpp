#include <iostream>
#include <string>

using namespace std;

int main () {

    string text;

    cout << "Write some word here: ";
    getline(cin, text);
    cout << text << endl;

    return 0;
}