#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib"); 
using namespace std;

void initWinSock(){
    WSADATA WSAData;
    int result = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if(result != 0){
        cerr << "WSAStartup failed." << result << endl;
        exit(1);
    }

}

int main(){

    initWinSock();
    cout << "Winsock initialized successfully!" << endl;
    return 0;
}