#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib");  // link thu vien ws2_32.lib de su dung cac ham cua thu vien nay
using namespace std;

#define DEFAULT_PORT "8888"

void initWinSock(){         // khai bao ham kieu void
    WSADATA WSAData;        // khai bao bien kieu struct WSADATA co ten WSAData
    int result = WSAStartup(MAKEWORD(2, 2), &WSAData);      // thu tuc truoc khi dung socket, goi ham WSAStartup va truyen cac tham so vao, su dung toan tu & de lay dia chi struct WSAData, ghi thong tin vao WSAData thong qua dia chi nay
    if(result != 0){
        cerr << "WSAStartup failed." << result << endl;
        exit(1);
    }

}

// dinh nghia function kieu SOCKET

SOCKET createSocket(){      
    struct addrinfo *result = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;      // ipv4
    hints.ai_socktype = SOCK_STREAM;        // type sockstream
    hints.ai_protocol = IPPROTO_TCP;        // proto TCP
    hints.ai_flags = AI_PASSIVE;        // make socket tobe listening for something (code server duoc su dung de lang nghe 1 ket noi den)

    // goi getaddrinfo va luu ket qua vao result de chuan bi bind

    int iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);     // cac tham so: dia chi IP local, port listen, dia chi struct thuoc tinh, dia chi ket qua luu tru thong tin socket (127.0.0.1:8888)
    if(iResult != 0){       // kiem tra loi
        cerr << "getaddressinfo failed: " << iResult << endl;
        exit(1);
    }

    // tao socket voi tham so lay tu result

    SOCKET serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);      
    if(serverSocket == INVALID_SOCKET){
        cerr << "Socket create failed" << endl;
        exit(1);
    }

    // bind socket vao dia chi IP:port

    iResult = bind(serverSocket, result->ai_addr, (int)result->ai_addrlen);
    if(iResult == SOCKET_ERROR){
        cerr << "Bind error!" << endl;
        exit(1);
    }

    return serverSocket;
}

void listenForConnection(SOCKET serverSocket){
    int iResult = listen(serverSocket, SOMAXCONN);
    if(iResult!=0){
        cerr << "Listen failed" << endl;
        exit(1);
    }
    cout << "Waiting for connection..." << endl;

}

SOCKET acceptConnection(SOCKET serverSocket){
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if(clientSocket == INVALID_SOCKET){
        cerr << "Accept failed;" << endl;
        exit(1);
    }

    cout << "Client Connected" << endl;

    return clientSocket;
}

// void sendMessage(SOCKET clientSocket, const string &message){
//     int iResult = send(clientSocket, message.c_str(), message.length(), 0);
//     if(iResult == SOCKET_ERROR){
//         cerr << "Send failed." << endl;
//         exit(1);
//     }
//     cout << "Message sent." << endl;
// }

void sendCommand(SOCKET clientSocket, const string &command){
    int iResult = send(clientSocket, command.c_str(), command.length(), 0);
    if(iResult == SOCKET_ERROR){
        cerr << "Send failed" << endl;
        exit(1);
    }
}

string receiveResult(SOCKET clientSocket){
    char buffer[10000];
    int iResult = recv(clientSocket, buffer, sizeof(buffer), 0);
    if(iResult > 0){
        buffer[iResult] = '\0';
    }else if(iResult == 0){
        cout << "Conection close!" << endl;
    }else {
        cerr << "Recv failed!" << endl;
    }

    return string(buffer);
}

int main(){

    initWinSock();
    cout << "Winsock initialized successfully!" << endl;

    SOCKET serverSocket = createSocket();
    cout << "Server socket created and bound to port " << DEFAULT_PORT << endl;

    listenForConnection(serverSocket);

    SOCKET clientSocket = acceptConnection(serverSocket);

    while(true){

        string command;
        cout << "Enter your command: " << endl;
        getline(cin, command);

        if(command == "exit"){
            break;
        }

        sendCommand(clientSocket, command);

        string result = receiveResult(clientSocket);
        cout << result << endl;

    // string message = "Connection established";
    // sendMessage(clientSocket, message);
    }

    return 0;
}