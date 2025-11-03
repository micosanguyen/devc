#include <iostream>
#include <fstream>

using namespace std;

void WriteToFile(const string &filename, const string &data);

int main(){
    WriteToFile("creds.txt", "Hello, I'm fcking loser");

}

void WriteToFile(const string &filename, const string &data){
    ofstream wfile(filename);
    if(!wfile.is_open()){
        cerr << "Failed to open file";
    }
    wfile << data;
    wfile.close();
    cout << "Data writen to " << filename << "\n";

}