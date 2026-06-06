
/* Notes
Features ng [ARM] Anime Record Management

Account Creation /
Account validation /

Dashboard
-Anime-
Anime name
'' Episode watched

-Manga-
Manga Name
'' Chapters Read

  [UNAVAILABLE FEATURES]
    [DASHBAORD]
    Calculation based features 
      - Total AVG of anime / manga
       [refer to 'struct accContents' sa global, nandon yung mga dashboard variables]
    [ACCOUNT]
      *privacy feature
  [NEED NG REFINEMENT]
  *  input validation (! accepts a blank input)
  * output sa terminal (! di ko forte output design ) 
     - you can use the 'global colored texts' may labels na din yan


1.3 UPDATE
-ADDED COUT FEATURE FOR DASHBOARD
=================================================================================================
MAY DOCUMENTATION NAMAN AKO AND KUNG MAY NAKALIMUTAN AKONG ILAGAY OR NEED NG ADDITIONAL FEATURE [Hope not complicated feature], 
JUST FORK THIS AND EDIT NIYO based dun sa naiisip niyo, THEN DO A PULL REQUEST SA AKIN.
PARA BAWAT UPDATE HINDI YUNG ORIG FILE YUNG NABABAGO 
MORE ON SAFETY LANG NG MAIN FILE NATIN, BACKUP BA GANUN.

=================================================================================================
*/



#include <iostream> 
#include <iomanip> //setw and setprecision
#include <fstream> // file management
#include <string> // string
#include <vector> // storage
#include <thread> // animations
#include <chrono> // animation (2) / for delay
using namespace std;

// global colored texts
  const  string yellow = "\033[33m";// yellow
  const  string blue = "\033[34m"; // for the borders
  const  string green = "\033[32m"; // green for success messages
  const  string reset = "\033[0m"; // back to white colored texts
  const  string red = "\033[1;31m"; // for error messages

//dashboard contents

struct Anime{
    string anime_name = "NONE";
    int anime_ep = 0;
};
struct Manga{
    string manga_name = "NONE";
    double manga_chpt = 0.0;
};

struct accContents{
   // Total Manga and Anime
  //string anime_name = "NONE";//  anime name is for the dashboard, so that we can display the anime name and episodes watched
  //int anime_ep = 0; // default value of 0 for the episodes and chapters, so that when we add it will be added to 0
  vector <Anime> anime_list; // list of animes, so that we can display it in the dashboard
  int totalSeeAnime = 0; // totalSeeAnime is for the dashboard, so that we can calculate the average of anime watched
  //string manga_name = "NONE"; // manga name is for the dashboard, so that we can display the manga name and chapters read
  //double manga_chpt = 0.0; // double because theres chapter with '10.5'
  vector <Manga> manga_list; // list of mangas, so that we can display it in the dashboard
  int totalReadManga = 0; // totalReadManga is for the dashboard, so that we can calculate the average of manga read

  
    /*not enough data to continue
    needed:
    -total minutes
    -total episodes / chapters
    */
    
    //proposed variables for the dashboard
   // double avgSeeAnime; formula : total minutes / total episodes
    //double avgReadManga; formula: totalReadManga / chapters
};
    
//Account verification
struct Account{
  string username;
  int pin;
  accContents content;
 //accContents content; // can access this when 'Account Match'
};

void loadToFile(vector<Account>&userAccount);
void saveToFile(const vector<Account> &userAccount); // runs when every changes happens like account creation, input changes or addition. 
void showColorfulWelcome();
void newUser();
void loading();

void delay(int x);

int main()
{
   //Storage / Database 
    vector<Account> userAccount;
    int initchoice = 0;
    string username;//input
    int pin;//input
    
    do{
        loadToFile(userAccount);
        showColorfulWelcome();
        cout << string (30,' ') << blue << string(43, '-') << reset << endl;
        cout << string (40,' ') << reset<< "1. Login" << endl;
        cout << string (40,' ') <<         "2. Create Account" << endl;
        cout << string (40,' ') <<          "3. Exit" << endl;
        cout << string (30,' ') << blue << string(43, '-') << reset << endl;
        
    // Menu Choice Logic
        cout << string (30,' ') << green << "Choice: " << reset;
        
        if (!(cin >> initchoice)) {
            cout << red << "\nError.... Please enter a number" << reset << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        


        // LOGIN LOGIC
        if (initchoice == 1) {
            cin.ignore(1000, '\n'); // Clear the buffer once
            
            cout << string (30,' ') << "Username (use _ for spaces): ";
            // Combine the input and the error check into one line
            if (!(cin >> username)) {
                cout << red << "Error identifying the input. Please try again" << reset << endl;
                cout << endl;
                delay(2);
                continue;
            }

            cout << string (30,' ') << "Password: ";
            if (!(cin >> pin)) {
                cout << red << "Error identifying the input. Please try again" << reset << endl;
                cout << endl;
                delay(2);
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
        
            //Pseudocode
            //Account Checking / Verification Thru LOGIN option
            /* if(haveAcc(username, pass)){
                    cout << "Login Successful\n";
                    break;
                }
                else{
                    cout << "Account Not Found\n";
                    continue;
                }*/
                
                //creates a temporary container because we can't access the vector directly using 'acc' 
                
                
            /*bool found =false;
            for( auto& acc: userAccount) {
                if (acc.username == username && acc.pin == pin){
                    found = true;
                    break;
                }
            }*/
            // for loop for finding the Account
            bool found = false; 
            int foundIndex = -1 ; 
            for (int i =0; i < userAccount.size(); i++){
                if(userAccount[i].username == username && userAccount[i].pin == pin){
                    found = true;
                    foundIndex = i;
                }
            }
            
            if(found){
                cout << string(30,' ') << green << "Login successful!" << reset << endl;
                Account &temp = userAccount[foundIndex];
                //Since we found the account, we can now access the content of the account using 'temp' as a reference to the found account in the vector
                
                cout << string (30,' ') <<  blue << "-----------------------------" << reset << endl;
                cout << string (35,' ') << yellow << "WELCOME, " << temp.username << reset<< endl;
                int choice1 =0;
                int new_ep = 0;
                double new_chpt= 0.0;
                
                do{
                    //parts of contents is the vector so that we can add multiple animes and mangas, and display it in the dashboard
                    // First, use the anime vector to store the anime name and episodes watched, then use the manga vector to store the manga name and chapters read, then use the totalSeeAnime and totalReadManga to calculate the average of anime watched and manga read, then display it in the dashboard
                    // by using a container like 'temp'

                    vector<Anime> &animeTemp = temp.content.anime_list;
                    vector<Manga> &mangaTemp = temp.content.manga_list;

                    cout << string (30,' ') << blue << "-----------------------------" << reset << endl;
                    cout << string (30,' ') <<"\t1. Anime" << endl;
                    cout << string (30,' ') << "\t2. Manga" << endl;
                    cout << string (30,' ') << "\t3. Dashboard" << endl;
                    cout << string (30,' ') << "\t4. Exit" << endl;
                    cout << string (30,' ') <<blue << "-----------------------------" << reset << endl;
                    cout << string (30,' ') << green << "Choice: " << reset;
                    cin >> choice1;

                    switch (choice1) {
                        case 1: { // ANIME LOGGER
                            cin.ignore(1000, '\n');
                            Anime freshAnime; 
                            int new_ep = 0;
                            

                            cout << string(35, ' ') << green << "Adding Anime Record..." << reset << endl;
                            cout << string(30, ' ') << "Anime name: ";
                            getline(cin, freshAnime.anime_name); 
                            cout << string(30, ' ') << "Episodes Watched: ";
                            cin >> new_ep;
                            freshAnime.anime_ep = new_ep;

                            // Scan vector through the clean shortcut handle
                            bool exists = false;
                            for (size_t i = 0; i < animeTemp.size(); i++) {
                                if (animeTemp[i].anime_name == freshAnime.anime_name) {
                                    animeTemp[i].anime_ep += new_ep; 
                                    cout << string (30,' ') << blue << "-----------------------------" << reset << endl;
                                    cout << "\n" << ""
                                    exists = true;
                                    break;
                                }
                            }

                            if (!exists) {
                                animeTemp.push_back(freshAnime);
                                temp.content.totalSeeAnime++; 
                            }

                            saveToFile(userAccount); 
                            cout << string (30,' ') << blue << "-----------------------------" << reset << endl;
                            cout << string(35, ' ') << green << "Anime updated!" << reset << endl;
                            cout << string (30,' ') << blue << "-----------------------------" << reset << endl;
                        } break;

                        case 2: { // MANGA LOGGER
                            cin.ignore(1000, '\n');
                            Manga freshManga; 
                            double new_chpt = 0.0;

                            cout << string(30,' ')<< green <<"Adding Manga Record" <<reset<<endl;
                            cout << string(30, ' ') << "Manga name: ";
                            getline(cin, freshManga.manga_name); 
                            cout << string(30, ' ') << "Chapters read: ";
                            cin >> new_chpt;
                            freshManga.manga_chpt = new_chpt;

                            // Scan vector through the clean shortcut handle
                            // Check if the manga already exists in the vector, 
                            // if it does, add the new chapters to the existing chapters, 
                            // if not, add the new manga to the vector
                            bool exists = false;
                            for (size_t i = 0; i < mangaTemp.size(); i++) {
                                if (mangaTemp[i].manga_name == freshManga.manga_name) {
                                    mangaTemp[i].manga_chpt += new_chpt; 
                                    exists = true;
                                    break;
                                }
                            }

                            if (!exists) {
                                mangaTemp.push_back(freshManga);
                                temp.content.totalReadManga++; 
                            }

                            saveToFile(userAccount); 
                            cout << string(30, ' ') << green << "Manga updated!" << reset << endl;
                        } break;

                        case 3: { // GRID DASHBOARD DISPLAY BLOCK
                            cout << "\n" << string(30, ' ') << yellow << "=== " << temp.username << "'s LIVE DATABASE ===" << reset << "\n\n";

                            if (animeTemp.empty() && mangaTemp.empty()) {
                                cout << string(30, ' ') << red << "No records found! Log some entries first." << reset << "\n";
                            }
                            else {
                                // --- ANIME GRID USING HANDLE ---
                                cout << string(25, ' ') << yellow << "[ANIME LOG]" << reset << "\n";
                                if (animeTemp.empty()) {
                                    cout << string(25, ' ') << "  (No anime entries registered yet)" << "\n\n";
                                } else {
                                    cout << string(25, ' ') << blue 
                                        << left << setw(10) << "INDEX" 
                                        << left << setw(30) << "ANIME NAME" 
                                        << left << setw(15) << "EPISODES" << reset << "\n";
                                    cout << string(25, ' ') << blue << string(55, '-') << reset << "\n";

                                    for (size_t i = 0; i < animeTemp.size(); i++) {
                                        cout << string(25, ' ') 
                                            << left << setw(10) << ("[" + to_string(i + 1) + "]") 
                                            << left << setw(30) << animeTemp[i].anime_name
                                            << left << setw(15) << animeTemp[i].anime_ep
                                            << "\n";
                                    }
                                    cout << string(25, ' ') << blue << string(55, '=') << reset << "\n\n";
                                }

                                // --- MANGA GRID USING HANDLE ---
                                cout << string(25, ' ') << yellow << "[MANGA LOG]" << reset << "\n";
                                if (mangaTemp.empty()) {
                                    cout << string(25, ' ') << "  (No manga entries registered yet)" << "\n\n";
                                } else {
                                    cout << string(25, ' ') << blue 
                                        << left << setw(10) << "INDEX" 
                                        << left << setw(30) << "MANGA NAME" 
                                        << left << setw(15) << "CHAPTER/S" << reset << "\n";
                                    cout << string(25, ' ') << blue << string(55, '-') << reset << "\n";

                                    for (size_t i = 0; i < mangaTemp.size(); i++) {
                                        cout << string(25, ' ') 
                                            << left << setw(10) << ("[" + to_string(i + 1) + "]") 
                                            << left << setw(30) << mangaTemp[i].manga_name
                                            << left << setw(15) << mangaTemp[i].manga_chpt
                                            << "\n";
                                    }
                                    cout << string(25, ' ') << blue << string(55, '=') << reset << "\n";
                                }

                                cout << "\n" << string(30, ' ') << "Press " << yellow << "Enter " << reset << "to go back to Menu";
                                cin.ignore(1000, '\n');
                                cin.get();
                            }
                        } break;
                    }
                }while(choice1 != 4);
            }
            else {
                cout << string (30,' ') <<  blue << "-----------------------------" << reset << endl;
                cout << string (30,' ') << red << "Account not found. Please check username and password." << reset << endl;
                cout << string (30,' ') <<  blue << "-----------------------------" << reset << endl;
                cout << endl;
                delay(2);
            }
            cin.ignore(1000,'\n');
            
        }


        //Create Account Logic
        else if (initchoice == 2){
            //Welcome message
            cin.ignore(1000,'\n');
            newUser();
            
            // ACCOUNT CREDENTIALS 
        Account temp;
            cout << string (30,' ') << "\nAccount Username (use _ for spaces): "<< yellow;
            cin >> temp.username;
            cout  << reset<<"Account  Password: "<< yellow;
        
            
            if (!(cin >> temp.pin)) {
                cout << string (30,' ') << red << "Error identifying the input. Please try again" << reset << endl;
                cout << endl;
                delay(2);
                
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            userAccount.push_back(temp);
            saveToFile(userAccount);
            loading();
            cout << string (30,' ') <<green << "\nAccount Saved"
                        << "\nAccount Created Successfully." 
                        << "\nYou can now switch to "
                        << yellow << "Login section "
                        << reset<<"to Start\n\n" << reset;
            delay(2);
            continue;
        }
        else if (initchoice == 3){
            return 0;//exit program

        }
        else{
            cout << string (30,' ') << red << "Only select from "<< endl;
            cout << string (30,' ') << red << string(43, '-') << reset << endl;
            cout << string (40,' ') << red << "1. Login" << endl;
            cout << string (40,' ') <<         "2. Create Account" << endl;
            cout << string (40,' ') <<          "3. Exit" << endl;
            cout << string (30,' ') << red << string(43, '-') << reset << endl;

            for (int i = 10 ; i > 0 ; i--){
                cout <<"\r" << string (30,' ') << red << "You will return to the main menu in "<< yellow << i << red << " seconds..." << reset << flush ;
                this_thread::sleep_for(chrono::seconds(1));
                continue;
            }
        }
        
    }while(initchoice !=3);
}




// UDF's
void showColorfulWelcome() {
    cout <<endl;
    cout << string (30,' ') << blue << "*******************************************" << reset << endl;
    cout << string (30,' ') << blue << "*                                         *" << reset << endl;
    cout << string (30,' ') << blue << "*        " << yellow << "A N I M E   R E C O R D  " << blue << "        *" << reset << endl;
    cout << string (30,' ') << blue << "*             " << yellow << "M A N A G E R  " << blue << "             *" << reset << endl;
    cout << string (30,' ') << blue << "*                                         *" << reset << endl;
    cout << string (30,' ') << green <<"*        SYSTEM ACCESS AUTHORIZED         *" << reset << endl;
    cout << string (30,' ') << blue << "*                                         *" << reset << endl;
    cout << string (30,' ') << blue << "*******************************************" << reset << endl;
}
void newUser(){
  cout << string (30,' ') << string(20,'=');
  cout << string (30,' ') << "Welcome, New user \n";
  cout << string (30,' ') << string(20,'=');
}

void loading(){
    for (int i=1; i <100;i++ ){
        cout <<string (30,' ') << "\rLoading " << i << flush  ;
         this_thread::sleep_for(chrono::milliseconds(30));
    }
}

void delay(int x){
    this_thread::sleep_for(chrono::seconds(x));
}

void saveToFile(const vector<Account>& userAccount) {
    // Open file stream for writing text line-by-line
    ofstream outfile("Accounts Database.txt");
    if (!outfile) return;

    for (const auto& acc : userAccount) {
        // 1. Save core user credentials
        outfile << acc.username << "\n" 
                << acc.pin << "\n";
        
        // 2. Save Anime vector size, then loop through each item
        outfile << acc.content.anime_list.size() << "\n";
        for (const auto& anime : acc.content.anime_list) {
            outfile << anime.anime_name << "\n" 
                    << anime.anime_ep << "\n";
        }

        // 3. Save Manga vector size, then loop through each item
        outfile << acc.content.manga_list.size() << "\n";
        for (const auto& manga : acc.content.manga_list) {
            outfile << manga.manga_name << "\n" 
                    << manga.manga_chpt << "\n";
        }

        // 4. Save structural dashboard counter metrics
        outfile << acc.content.totalSeeAnime << "\n" 
                << acc.content.totalReadManga << "\n";
    }
    outfile.close(); // Close stream to flush memory buffer safely
}

void loadToFile(vector<Account>& userAccount) {
    ifstream infile("Accounts Database.txt");
    if (!infile) return; // File doesn't exist yet, return safely

    userAccount.clear(); // Wipe the leftovers, not the Contents of the Database
    Account temp;

    // Outer loop continues as long as a username exists
    while (getline(infile, temp.username)) {
        infile >> temp.pin;
        infile.ignore(); // Clean leftover newline character after number

        temp.content.anime_list.clear();// Clear the vectors, like cleaning a plate before eating again.
        temp.content.manga_list.clear();

        // 1. Rebuild the Anime Vector List
        int animeSize = 0;
        infile >> animeSize;
        infile.ignore(); // Clean newline after reading vector size
        
        for (int i = 0; i < animeSize; i++) {
            Anime a;
            getline(infile, a.anime_name); // Reads names with spaces safely
            infile >> a.anime_ep;
            infile.ignore(); // Clean newline after reading episodes
            temp.content.anime_list.push_back(a);
        }

        // 2. Rebuild the Manga Vector List
        int mangaSize = 0;
        infile >> mangaSize;
        infile.ignore(); 
        
        for (int i = 0; i < mangaSize; i++) {
            Manga m;
            getline(infile, m.manga_name); // Reads names with spaces safely
            infile >> m.manga_chpt;
            infile.ignore(); // Clean newline after reading chapters
            temp.content.manga_list.push_back(m);
        }

        // 3. Extract baseline metric tracking totals
        infile >> temp.content.totalSeeAnime >> temp.content.totalReadManga;
        infile.ignore(); // Flush final line ending carriage return

        userAccount.push_back(temp);
    }
    infile.close();
}
