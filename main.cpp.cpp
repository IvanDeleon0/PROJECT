#include "accounts.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
