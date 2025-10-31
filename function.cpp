#include <iostream>
#include <string>

using namespace std;

int add(int a, int b){
    int sum = a + b;
    return sum;
}

int main(){
    int x;
    int y;
    int results;

    cout << "Insert x: ";
    cin >> x;

    cout << "Insert y: ";
    cin >> y;

    results = add(x, y);
    cout << "The results is: " << results << endl;
}