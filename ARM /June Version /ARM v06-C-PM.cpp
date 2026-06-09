
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

struct Anime {
	string anime_name = "NONE";
	int anime_ep = 0;
};
struct Manga {
	string manga_name = "NONE";
	double manga_chpt = 0.0;
};

struct accContents {
	// Total Manga and Anime
	//string anime_name = "NONE";//  anime name is for the dashboard, so that we can display the anime name and episodes watched
	//int anime_ep = 0; // default value of 0 for the episodes and chapters, so that when we add it will be added to 0
	vector <Anime> anime_list; // list of animes, so that we can display it in the dashboard
	int totalSeeAnime = 0; // totalSeeAnime is for the dashboard, so that we can calculate the average of anime watched
	//string manga_name = "NONE"; // manga name is for the dashboard, so that we can display the manga name and chapters read
	//double manga_chpt = 0.0; // double because theres chapter with '10.5'
	vector <Manga> manga_list; // list of mangas, so that we can display it in the dashboard
	int totalReadManga = 0; // totalReadManga is for the dashboard, so that we can calculate the average of manga read
};

//Account verification
struct Account {
	string username;
	int pin;
	accContents content;
	//accContents content; // can access this when 'Account Match'
};

void loadToFile(vector<Account>&userAccount);
void saveToFile(const vector<Account> &userAccount); // runs when every changes happens like account creation, input changes or addition.
void createAccount(vector <Account> &userAccount); // creates account and for clean function call
void exitAnimation();
void dashboard(Account &temp, int viewOption);
void deleteManga(Account &temps);
void deleteAnime(Account &temps);
void searchRecord(Account &acc, string searchName);
void showColorfulWelcome();
void newUser();
void loading();
bool isDuplicate(const vector <Account> &userAccount, const string& duplicate);
void mock(); // cout under construction
void delay(int x);

int main()
{
	//Storage / Database
	vector<Account> userAccount;
	int initchoice = 0;
	string username;//input
	int pin;//input
	loadToFile(userAccount);

	do {

		showColorfulWelcome();
		cout << string (30,' ') << blue << string(43, '-') << reset << endl;
		cout << string (40,' ') << reset<< "1. Login" << endl;
		cout << string (40,' ') <<         "2. Create Account" << endl;
		cout << string (40,' ') <<          "3. Account Recovery" << endl;
		cout << string (40,' ') <<          "4. Exit" << endl;
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
				cin.clear();
				cin.ignore(1000,'\n');
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
			for (int i =0; i < userAccount.size(); i++) {
				if(userAccount[i].username == username && userAccount[i].pin == pin) {
					found = true;
					foundIndex = i;
				}
			}

			if(found) {
				cout << string(40,' ') << green << "Login successful!" << reset << endl;
				delay(2);
				Account &temp = userAccount[foundIndex];
				//Since we found the account, we can now access the content of the account using 'temp' as a reference to the found account in the vector

				cout << string (30,' ') <<  blue << "-----------------------------" << reset << endl;
				cout << string (35,' ') << yellow << "        WELCOME, " << temp.username << reset<< endl;
				int choice1 =0;
				int new_ep = 0;
				double new_chpt= 0.0;

				do {
					//parts of contents is the vector so that we can add multiple animes and mangas, and display it in the dashboard
					// First, use the anime vector to store the anime name and episodes watched, then use the manga vector to store the manga name and chapters read, then use the totalSeeAnime and totalReadManga to calculate the average of anime watched and manga read, then display it in the dashboard
					// by using a container like 'temp'

					vector<Anime> &animeTemp = temp.content.anime_list;
					vector<Manga> &mangaTemp = temp.content.manga_list;

					cout << string(30,' ') << blue
					     << "=================================================\n" << reset;

					cout << string(30,' ') << yellow
					     << "            ANIME RECORD MANAGER\n" << reset;

					cout << string(30,' ') << blue
					     << "=================================================\n" << reset;

					cout << string(30,' ') << "| [1] Add Anime      | [2] Add Manga      |\n";
					cout << string(30,' ') << "|------------------------------------------|\n";

					cout << string(30,' ') << "| [3] Search         | [4] Dashboard      |\n";
					cout << string(30,' ') << "|------------------------------------------|\n";

					cout << string(30,' ') << red
					     << "| [5] Delete Manga   | [6] Delete Anime   |\n" << reset;

					cout << string(30,' ') << "|------------------------------------------|\n";

					cout << string(30,' ') << yellow
					     << "| [7] Privacy        | [8] Log Out        |\n" << reset;

					cout << string(30,' ') << blue
					     << "=================================================\n" << reset;
					cout <<string(30,' ') << green << "Choice: "<<reset;
					cin >> choice1;
					switch (choice1) {
					case 1: { // ANIME LOGGER
						cin.ignore(1000, '\n');
						Anime freshAnime;
						int new_ep = 0;

						cout << yellow << string(30,' ')<<"Type 'exit' or 'cancel' to go back.\n";
						cout << reset << string(30,' ')<< "Use '_' as spaces\n";
						cout << string(35, ' ') << green << "Adding Anime Record..." << reset << endl;
						cout << string(30, ' ') << "Anime name: ";
						getline(cin, freshAnime.anime_name);

						if (freshAnime.anime_name == "exit" || freshAnime.anime_name == "cancel") {
							cout <<  string(30,' ')<<  "Cancelled anime input.\n";
							break; // exit case 1
						}

						cout << string(30, ' ') << "Episodes Watched: ";
						cin >> new_ep;
						freshAnime.anime_ep = new_ep;

						// Scan vector through the clean shortcut handle
						bool exists = false;
						for (size_t i = 0; i < animeTemp.size(); i++) {
							if (animeTemp[i].anime_name == freshAnime.anime_name) {
								animeTemp[i].anime_ep += new_ep;
								cout << string (30,' ') << "Adding "<< new_ep << "episodes with "<< animeTemp[i].anime_ep << "episodes\n";
								cout << string (30,' ') << blue << "-----------------------------" << reset << endl;
								cout << "\n" << "";
								exists = true;
								break;
							}
						}

						if (!exists) { // means it is a "new anime"
							animeTemp.push_back(freshAnime);
							temp.content.totalSeeAnime++; // adds one to the record of anime
						}

						saveToFile(userAccount);
						cout << string (30,' ') << blue << "-----------------------------" << reset << endl;
						cout << string(35, ' ') << green << "Anime updated!" << reset << endl;
						cout << string (30,' ') << blue << "-----------------------------" << reset << endl;
						cout << string(30,' ') << green << "Saved successfully!" << reset << "\n";
					}
					break;

					case 2: { // MANGA LOGGER
						cin.ignore(1000, '\n');
						Manga freshManga;
						double new_chpt = 0.0;

						cout << yellow << string(30,' ')<<"Type 'exit' or 'cancel' to go back.\n";
						cout << reset << string(30,' ')<< "Use '_' as spaces\n";
						cout << string(30,' ')<< green <<"Adding Manga Record" <<reset<<endl;
						cout << string(30, ' ') << "Manga name: ";
						getline(cin, freshManga.manga_name);

						if (freshManga.manga_name == "exit" || freshManga.manga_name == "cancel") {
							cout <<  string(30,' ')<<  "Cancelled anime input.\n";
							break; // exit case 1
						}
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
					}
					break;
					case 3: {
						cin.ignore(1000, '\n');

						string searchName;

						cout << "\n";
						cout << string(30,' ') << blue
						     << "====================================\n";
						cout << string(30,' ') << yellow
						     << "        SEARCH RECORDS\n";
						cout << string(30,' ') << blue
						     << "====================================\n"
						     << reset;

						cout << string(30,' ') << green
						     << "Enter Title: "
						     << reset;

						getline(cin, searchName);
						searchRecord(temp, searchName);
						delay(5);

						cout << "\n";
						break;
					}
					case 4: { // GRID DASHBOARD DISPLAY BLOCK
						dashboard(temp, 3);
					}
					break;

					case 5: { // DELETE MANGA
						deleteManga(temp);
						saveToFile(userAccount);
					}
					break;

					case 6: { // DELETE ANIME
						deleteAnime(temp);
						saveToFile(userAccount);
					}
					break;
					case 7: {
						mock();
						delay(3);
					}
					break;
					case 8: {
						saveToFile(userAccount);
					}
					break;
					default: {
						cout << red << string(30,' ')<< "Invalid input\n";
					}
					break;
					}
				} while(choice1 != 8);
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
		else if (initchoice == 2) {
			createAccount(userAccount);

		}
		else if(initchoice == 3) {
			mock();
			delay(3);

		}
		else if (initchoice == 4) {
			saveToFile(userAccount);
			exitAnimation();
			return 0;//exit program

		}
		else {
			cout << string (30,' ') << red << "Only select from "<< endl;
			cout << string (30,' ') << red << string(43, '-') << reset << endl;
			cout << string (40,' ') << red << "1. Login" << endl;
			cout << string (40,' ') <<         "2. Create Account" << endl;
			cout << string (40,' ') <<          "3. Exit" << endl;
			cout << string (30,' ') << red << string(43, '-') << reset << endl;

			for (int i = 5 ; i > 0 ; i--) {
				cout <<"\r" << string (30,' ') << red << "You will return to the main menu in "<< yellow << i << red << " seconds..." << reset << flush ;
				this_thread::sleep_for(chrono::seconds(1));
				continue;
			}

		}

	} while(initchoice !=4);
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
void newUser() {
	cout << "\n\n";
	cout << string(30, ' ') << blue << "=============================\n" << reset;
	cout << string(30, ' ') << "        NEW USER DETECTED\n";
	cout << string(30, ' ') << "=============================\n";
	cout << string(30, ' ') << green << "   Welcome to ARM System!\n" << reset;
	cout << string(30, ' ') << "=============================\n\n";
}

void loading() {
	for (int i=1; i <100; i++ ) {
		cout <<string (30,' ') << "\rLoading " << i << flush  ;
		this_thread::sleep_for(chrono::milliseconds(30));
	}
}

void dashboard(Account &temp, int viewOption) {

	vector<Anime> &animeTemp = temp.content.anime_list;
	vector<Manga> &mangaTemp = temp.content.manga_list;

	cout << "\n" << string(25, ' ')
	     << yellow << "=== " << temp.username << "'s DASHBOARD ==="
	     << reset << "\n\n";

	// ===================== ANIME =====================
	if (viewOption == 1 || viewOption == 3) {

		cout << string(25, ' ') << yellow << "===== ANIME TABLE =====" << reset << "\n\n";

		cout << left << setw(25) << "ANIME NAME"
		     << setw(15) << "EPISODES" << "\n";

		cout << string(45, '-') << "\n";

		int totalEpisodes = 0;

		for (auto &a : animeTemp) {
			cout << left << setw(25) << a.anime_name
			     << setw(15) << a.anime_ep << "\n";

			totalEpisodes += a.anime_ep;
		}

		double avgEp = animeTemp.empty()
		               ? 0
		               : (double)totalEpisodes / animeTemp.size();

		cout << string(45, '-') << "\n";
		cout << left << setw(25) << "TOTAL"
		     << setw(15) << totalEpisodes << "\n";

		cout << left << setw(25) << "AVERAGE"
		     << setw(15) << avgEp << "\n\n";
	}

	// ===================== MANGA =====================
	if (viewOption == 2 || viewOption == 3) {

		cout << string(25, ' ') << yellow << "===== MANGA TABLE =====" << reset << "\n\n";

		cout << left << setw(25) << "MANGA NAME"
		     << setw(15) << "CHAPTERS" << "\n";

		cout << string(45, '-') << "\n";

		double totalChapters = 0;

		for (auto &m : mangaTemp) {
			cout << left << setw(25) << m.manga_name
			     << setw(15) << m.manga_chpt << "\n";

			totalChapters += m.manga_chpt;
		}

		double avgCh = mangaTemp.empty()
		               ? 0
		               : totalChapters / mangaTemp.size();

		cout << string(45, '-') << "\n";
		cout << left << setw(25) << "TOTAL"
		     << setw(15) << totalChapters << "\n";

		cout << left << setw(25) << "AVERAGE"
		     << setw(15) << avgCh << "\n\n";
	}
	// ===================== EMPTY CASE =====================
	if (animeTemp.empty() && mangaTemp.empty()) {
		cout << string(25, ' ') << "(No records found)\n";
	}
}
void delay(int x) {
	this_thread::sleep_for(chrono::seconds(x));
}
void deleteManga(Account &acc) {

	vector<Manga> &mangaTemp = acc.content.manga_list;

	cout << red << string(35,' ') << "============================\n";
	cout << string(35,' ') << "     DELETE MANGA MENU\n";
	cout << string(35,' ') << "============================\n" << reset;

	if (mangaTemp.empty()) {
		cout << string(35,' ') << "No manga to delete.\n";
		delay(2);
		return;
	}

	// show list
	for (size_t i = 0; i < mangaTemp.size(); i++) {
		cout << string(30,' ')
		     << i + 1 << ". "
		     << mangaTemp[i].manga_name << "\n";
	}

	cout << "\n" << string(30,' ') << "Enter number to delete: ";
	int index;
	cin >> index;

	if (index < 1 || index > mangaTemp.size()) {
		cout << string(30,' ') << red << "Invalid index!\n" << reset;
		return;
	}

	cout << string(30,' ') << "Are you sure? (y/n): ";
	char confirm;
	cin >> confirm;

	if (confirm == 'y' || confirm == 'Y') {
		mangaTemp.erase(mangaTemp.begin() + (index - 1));
		cout << string(30,' ') << green << "Manga deleted successfully!\n" << reset;
	} else {
		cout << string(30,' ') << yellow << "Cancelled.\n" << reset;
	}
}
void deleteAnime(Account &acc) {

	vector<Anime> &animeTemp = acc.content.anime_list;

	cout << red << string(30,' ') << "============================\n";
	cout << string(30,' ') << "     DELETE ANIME MENU\n";
	cout << string(30,' ') << "============================\n" << reset;

	if (animeTemp.empty()) {
		cout << string(30,' ') << "No anime to delete.\n";
		delay(2);
		return;
	}

	for (int i = 0; i < animeTemp.size(); i++) {
		cout << string(30,' ')
		     << i + 1 << ". "
		     << animeTemp[i].anime_name << "\n";
	}

	cout << "\n" << string(30,' ') << "Enter number to delete: ";
	int index;
	cin >> index;

	if (index < 1 || index > animeTemp.size()) {
		cout << string(30,' ') << red << "Invalid index!\n" << reset;
		return;
	}

	cout << string(30,' ') << "Are you sure? (y/n): ";
	char confirm;
	cin >> confirm;

	if (confirm == 'y' || confirm == 'Y') {
		animeTemp.erase(animeTemp.begin() + (index - 1));
		cout << string(30,' ') << green << "Anime deleted successfully!\n" << reset;
	} else {
		cout << string(30,' ') << yellow << "Cancelled.\n" << reset;
	}
}
void createAccount(vector <Account>&userAccount) {
	//Welcome message
	cin.ignore(1000,'\n');
	newUser();

	// ACCOUNT CREDENTIALS
	Account temp;
	cout << string (30,' ') << yellow <<"Use '_' for spaces)" <<endl << reset << "\nAccount Username: "<< yellow;
	cin >> temp.username;

	while (isDuplicate(userAccount, temp.username)) {
            cout << red << "Username already taken." << reset << endl;
        
            cout << "Enter another username: ";
            cin >> temp.username;
    }
	cout  << reset<<"Account  Password: "<< yellow;


	while (!(cin >> temp.pin)) {
		cout << string (30,' ') << red << "Error identifying the input. Please try again" << reset << endl;
		cout << endl;
		delay(2);

		cin.clear();
		cin.ignore(1000, '\n');

		cout << "Account Password: ";
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
}
void mock() {
	cout << string(40,' ')<<yellow<<"Feature Under Construction. \n";
}
void exitAnimation() {

	cout << "\n\n";
	cout << string(30, ' ') << "Shutting down system...\n\n";

	for (int i = 0; i <= 30; i++) {

		cout << green << "\r" << string(30, ' ')
		     << "[";

		for (int j = 0; j < i; j++) cout << "#";
		for (int j = i; j < 30; j++) cout << " ";

		cout << "] " << (i * 100 / 30) << "%";
		cout << flush << reset;

		this_thread::sleep_for(chrono::milliseconds(80));
	}
	cout << "\n\n";
	cout << string(30, ' ') << yellow<< "System exited successfully.\n";
}
void searchRecord(Account &acc, string searchName) {

	if(searchName.empty()) {
		cout << red <<string(30,' ')
		     << "\nSearch field cannot be empty.\n"
		     << reset;
		return;
	}
	vector<Anime> &animeTemp = acc.content.anime_list;
	vector<Manga> &mangaTemp = acc.content.manga_list;

	bool animeFound = false;
	bool mangaFound = false;

	cout << endl;
	cout << string(30,' ') << blue
	     << "====================================\n";
	cout << string(30,' ') << yellow
	     << "         SEARCH RESULTS\n";
	cout << string(30,' ') << blue
	     << "====================================\n"
	     << reset;

	// ================= ANIME =================

	cout << string(30,' ') << yellow
	     << "[ ANIME LIST ]\n"
	     << reset;

	for(auto &anime : animeTemp) {

		if(anime.anime_name.find(searchName) != string::npos) {

			cout << string(30,' ') << green
			     << "FOUND!\n"
			     << reset;

			cout << string(30,' ')
			     << "Title    : "
			     << anime.anime_name << endl;

			cout << string(30,' ')
			     << "Episodes : "
			     << anime.anime_ep << endl;

			cout << string(30,' ') << blue
			     << "-----------------------------\n"
			     << reset;

			animeFound = true;
		}
	}

	if(!animeFound) {

		cout << string(30,' ') << red
		     << "\"" << searchName << "\" "
		     << "was NOT FOUND in Anime Records.\n"
		     << reset;
	}

	cout << endl;

	// ================= MANGA =================

	cout << string(30,' ') << yellow
	     << "[ MANGA LIST ]\n"
	     << reset;

	for(auto &manga : mangaTemp) {

		if(manga.manga_name.find(searchName) != string::npos) {

			cout << string(30,' ') << green
			     << "FOUND!\n"
			     << reset;

			cout << string(30,' ')
			     << "Title    : "
			     << manga.manga_name << endl;

			cout << string(30,' ')
			     << "Chapters : "
			     << manga.manga_chpt << endl;

			cout << string(30,' ') << blue
			     << "-----------------------------\n"
			     << reset;

			mangaFound = true;
		}
	}

	if(!mangaFound) {

		cout << string(30,' ') << red
		     << "\"" << searchName << "\" "
		     << "was NOT FOUND in Manga Records.\n"
		     << reset;
	}

	cout << endl;

	cout << string(30,' ') << blue
	     << "====================================\n"
	     << reset;
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
		if(animeSize > 1000) {
			cout << "Anime Contents exceeded what the program can handle";
		}
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

// HELLO WANWAN
// i'll do the UDF's template for you to work on

// Duplicate Username Detection
bool isDuplicate(const vector <Account> &userAccount, const string& duplicate) {

	// range based loop instead of using the ordinary "for loop"
	for(const auto& orig: userAccount) {
		if (orig.username == duplicate) {
			return true; // duplicate found
		}
	}
	return false ; // no duplicate found
}

