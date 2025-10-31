#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(){
    try{
        int a, b;
        int devide;
        cout << "Insert a: " << endl;
        cin >> a;
        cout << "Insert b: " << endl;
        cin >> b;

        if(b == 0){
            throw runtime_error("Khong cho chia cho 0");
        }else{
            devide = (a / b);
            cout << "Result: " << devide << endl;
        }
    } catch (runtime_error e){
        cerr << "Error: " << e.what();
    }
    return 0;
}