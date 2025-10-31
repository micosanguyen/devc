#include <iostream>
#include <fstream>

using namespace std;

void log(const string &text){

    ofstream wkey("keylog.txt", ios::app);
    if(wkey.is_open()){
        wkey << text << endl;
        wkey.close();

    }
}

int main(){


}