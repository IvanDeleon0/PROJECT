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

int main()
{
    string username;
    string pass;

    cout << "LOGIN\n";
    
    cout << "Username: ";
    cin >> username;
    
    cout << "Password: ";
    cin >> pass;

    if(haveAcc(username, pass)){
        cout << "Login Successful\n";
    }
    else{
        cout << "Account Not Found\n";
    }

    return 0;
}