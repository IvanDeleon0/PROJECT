#include "accounts.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool haveAcc(string username, string pass){
    
    ifstream file("accounts.txt");
    
    string fileUser, filePass;

    if(!file){
        cout << "Error opening account database.\n";
        return false;
    }

    while(file >> fileUser >> filePass){
        if(username == fileUser && pass == filePass){
            return true;
        }
    }

    return false;
}
