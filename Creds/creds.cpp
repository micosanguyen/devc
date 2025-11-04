#include <iostream>
#include <fstream>
#include <windows.h>
#include <wincred.h>

#pragma comment(lib, "advapi32.lib");

using namespace std;

void WriteToFile(const string &filename, const string &data);
void listCredentials();

int main(){
    // WriteToFile("creds.txt", "Hello, I'm fcking loser");
    listCredentials();

}

void listCredentials(){
    DWORD creds_count;
    PCREDENTIAL *results_credentials_array; // khai bao con tro tro den mang creds tra ve

    if(CredEnumerate(NULL, 0, &creds_count, &results_credentials_array)){ // ham nay se truy van creds trong windows manager va tra ve so luong creds, dia chi cua mang creds neu co (TRUE, FALSE) https://learn.microsoft.com/en-us/windows/win32/api/wincred/nf-wincred-credenumeratew?utm_source=chatgpt.com
        cout << "Found creds: " << creds_count << "\n";
        for(DWORD i = 0; i < creds_count; i++){
            cout << "Target: " << results_credentials_array[i] -> TargetName << "\n";
        }
        CredFree(results_credentials_array);
    }else{
        cerr << "Failed to enumerate credentials" << GetLastError() << "\n";
    }
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