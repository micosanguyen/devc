#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(){

    ofstream wfile("mikasa.txt", ios::app);
    if(wfile.is_open()) {
        wfile << "I am a loser!" << endl;
        wfile << "Fcking loser!" << endl;
        wfile.close();
    } else {
        cout << "Error!";
    }

    ifstream rfile("mikasa.txt", ios::in);
    string line;
    if(rfile.is_open()){
        
        while (getline(rfile, line)) {
        cout << line << endl; }

        rfile.close();
    } else {
        cout << "Error!";
    }
    return 0;
}