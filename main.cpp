
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// global colored texts
  const  string blue = "\033[34m"; // for the borders
  const  string green = "\033[32m"; // green for success messages
  const string reset = "\033[0m"; // back to white colored texts
  const string red = "\033[1;31m"; // for error messages

void showColorfulWelcome() {
    
    cout << blue << "*******************************************" << reset << endl;
    cout << blue << "* *" << reset << endl;
    cout << "  " << green << "      SYSTEM ACCESS AUTHORIZED       " << reset << endl;
    cout << blue << "* *" << reset << endl;
    cout << blue << "*******************************************" << reset << endl;
}

int main()
{
    string username;
    string pass;
    int initchoice = 0;

    showColorfulWelcome();
    while(true){
    
    cout << "1. LOGIN\n";
    cout << "2. Create Account"<<endl;
    cout << "3. Exit"<<endl;
    
   // Menu Choice Logic
    cout << green << "Choice: " << reset;
    
    if (!(cin >> initchoice)) {
        cout << red << "\nError.... Please enter a number" << reset << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        continue;
    }

    if (initchoice == 1) {
        cin.ignore(1000, '\n'); // Clear the buffer once
        
        cout << "Username: ";
        // Combine the input and the error check into one line
        if (!(getline(cin, username))) {
            cout << red << "Error identifying the input. Please try again" << reset << endl;
            continue;
        }

        cout << "Password: ";
        if (!(cin >> pass)) {
            cout << red << "Error identifying the input. Please try again" << reset << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        
          //Account Checking / Verification Thru LOGIN option
           /* if(haveAcc(username, pass)){
                cout << "Login Successful\n";
                break;
            }
            else{
                cout << "Account Not Found\n";
                continue;
            }*/
        
    }
    else if (initchoice == 2){
    // account registration logic
    }
    else if (initchoice == 3){
        return 0;//exit program

      }
    }
}
