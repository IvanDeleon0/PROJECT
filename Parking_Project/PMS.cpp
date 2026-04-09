#include <iostream>
#include <vector> // Storage
#include <thread>   // Cout Line Control
#include <chrono> // Delay
#include <ctime>
#include <string> 
#include <fstream>

using namespace std;

  const  string yellow = "\033[33m";// yellow
  const  string blue = "\033[34m"; // for the borders
  const  string green = "\033[32m"; // green for success messages
  const string reset = "\033[0m"; // back to white colored texts
  const string red = "\033[1;31m"; // for error messages


//layout stored in vector
struct Vehicle {
    string timeIn;
    string timeOut;
    string plateNum;
    string ticketNum;
    string vehicleType;
    double fee;
    bool isParked = false;
};


string generateTicket(vector <Vehicle> &records);
void parkvehicle(vector<Vehicle>&records);
void generatingLoad();
void delay();
void viewParked(const vector <Vehicle>&records);
void savetoFile(const vector<Vehicle> &records);
void loadFromFile(vector<Vehicle> &records);

int main(){
    vector<Vehicle> records; // the <Vehicle> introduce the struct Vehicle as the source or layout of the vector content
    loadFromFile(records);
    // Entrance Interface
    int choice = 0;

    do{
        // Main Interface Choices
        
        cout << "\n\n\n\n\n"<<reset;
        cout << "\t    Vehicle Type     Per Hour rate    "<<endl;
        cout << "\t   [Cars | SUV ]           50         " <<endl;
        cout << "\t      [ Van ]              55         " <<endl;
        cout << "\t   [ Motorcycle ]          30         " <<endl;
        cout << "\t      [ Bus ]              80         " <<endl;
        
        cout << green<<  "\nGrace period: First 30 min is free."<<reset <<endl;
        
        cout <<string(40, '=') << endl;
        
        cout << "\t 1. Park vehicle\n";
        cout << "\t 2. Exit vehicle\n";
        cout << "\t 3. View Parked Cars\n";
        cout << "\t 4. Search Car\n";
        cout << "\t 5. Exit\n";
        cout << "\tOption: ";
        cin >> choice;
        cin.ignore(1000, '\n');
        
        switch(choice){
            case 1: {
                parkvehicle(records); 
            }break;
            case 2: {
                cout<< red << "Feature Unavailable" <<endl;
                delay();
                //exitVehicle();
            } break;
            case 3: {
                cout<< red<< "Feature Experimental ";
                viewParked(records);
                delay();
            }break;
            case 4: {
                cout<< red << "Feature Unavailable";
                delay();
            }break;
            case 5: {
                cout << green << "Exiting..." << reset;
                delay();
            }break;
            default:{
                cout<< "Only Choose from [1-5]...";
                delay();
            }break;
        }
        
    }while(choice != 5);
    
    cout << "Thank you for using our Service.." <<endl; // Exit Message
    cout <<  string(40,'=') << endl;
    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(1500));
    return 0;
}


void parkvehicle(vector<Vehicle>&records){
    Vehicle v;
    cout << string (30, '=') << endl;
    
    v.ticketNum = generateTicket(records);
    generatingLoad();
    cout <<endl << string(30, '=') << endl;
    cout << "\n\tParking Ticket Code: "<< yellow << v.ticketNum << reset << endl;;
    
    cout <<string(30, '=') << endl;
    cout << "Vehicle Type [Cars | SUV | Van | Motorcycle | Bus ]"<<endl;
    
    cout << "Type : " << yellow;
    cin  >> v.vehicleType;
    
    //input validation
   /* if(cin.fail()){
        cout << 
    }*/
    
    cout << reset << "Plate Number: " << yellow;
    cin >> v.plateNum;
    
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    struct tm* parts = localtime(&now_c);

    char buf[20];
    // Format: 2026-04-09_15:30:00 (No spaces, no newlines)
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H:%M:%S", parts);
    v.timeIn = string(buf);

    
    v.timeOut = "NONE"; // default value, will be updated on exit
    v.fee = 0; // zero since its just the entrance, fee will be calculated on exit
    v.isParked = true;
    
    records.push_back(v); // save
    savetoFile(records); // save to file after every new entry
    cout << string(40,'=');
    cout << reset<< "\nREMEMBER YOUR CODE TO CLAIM BACK YOUR VEHICLE\n";
    cout << "Parking Ticket Code: "<< yellow << v.ticketNum << endl;
    cout << string(40,'=');
    cout <<"\nPress "<< yellow << "ENTER "<< reset << "to return to the menu";
    cin.ignore(1000,'\n');
}

string generateTicket(vector <Vehicle> &records){
    auto now = chrono::system_clock::now();
    auto time_point = chrono::system_clock::to_time_t(now);
    // Format: TKT - seconds - sequence number
    return "TKT-" + to_string(time_point) + "-" + to_string(records.size() + 1);
    
};

void generatingLoad(){
    for (int i=1;i <= 100; i++){
    cout << "\rGenerating "<< i << " % "<<flush;
    this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void delay(){
    cout << " ";
    this_thread::sleep_for(chrono::milliseconds(1500));
}
void viewParked(const vector <Vehicle> &records){
    cout << green << " \n Viewing [Parked Cars] \n" << reset;
    delay();

    bool found = false;
    for(int i= 0; i < records.size() ; i++){
        if (records[i].isParked == true){
            cout << "Vehicle Type: "<< records[i].vehicleType 
                 << " ---- Plate Number: " << records[i].plateNum << endl;
            found = true;
        }
        
    }
    if(!found){
        cout << red << "There is no currently Parked Cars Recorded.\n\n" << reset;
    }
    cout <<  string(40,'=') << endl;
     cout <<"\nPress "<< yellow << "ENTER "<< reset << "to return to the menu";
    cin.ignore(1000,'\n');
}
void savetoFile(const vector<Vehicle> &records){
    ofstream file("parking_records.txt", ios::app);

    if (!file) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

     const Vehicle& v = records.back(); // Get the last parked vehicle
        file << v.ticketNum << " "
             << v.vehicleType << " "
             << v.plateNum << " "
             << v.timeIn << " "
             << v.timeOut << " "
             << v.fee << " "
             << v.isParked << endl;
    
     file.close();
}

void loadFromFile(vector<Vehicle> &records){
    ifstream file("parking_records.txt");
    if (file.is_open()) {
        Vehicle v;
        while (file >> v.ticketNum 
                    >> v.vehicleType    
                    >> v.plateNum
                    >> v.timeIn
                    >> v.timeOut
                    >> v.fee
                    >> v.isParked) {
            records.push_back(v);
        }
        file.close();
    }
}