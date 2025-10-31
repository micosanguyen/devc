#include <iostream>
#include <string>

using namespace std;

template <typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b);

int main(){

    cout << "Result: " << add(10, 10.5) << endl;
    return 0;
}

template <typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b){

    return a + b;
}