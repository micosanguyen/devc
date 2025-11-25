#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib");  // link thu vien ws2_32.lib de su dung cac ham cua thu vien nay
using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "8888"

void initClientSocket(){
    WSADATA WSAData;
    int result = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if(result != 0){
        cerr << "WSAStartup error " << result << endl;
        exit(1);
    }

}

SOCKET createClientSocket(){
    struct addrinfo *result = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int iResult = getaddrinfo(SERVER_IP, SERVER_PORT, &hints, &result);
    if(iResult != 0){
        cerr << "Getaddrinfo failed" << endl;
        exit(1);
    }

    SOCKET clientSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(clientSocket == INVALID_SOCKET){
        cerr << "Socket create failed" << endl;
        exit(1);
    }

    return clientSocket;
}

int main(){
    initClientSocket();
    SOCKET clientSocket = createClientSocket();

    cout << "Socket client create" << endl;

    return 0;
}