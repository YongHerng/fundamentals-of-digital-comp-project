// Zoom Meeting Assistant

#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

struct Meeting {
    string topic;
    string id;
    int duration;
    int totalParticipants;
    bool enableWaitingRoom;
    bool scheduled = false;
};

struct Participant {
    string name;
    bool microphoneOn;
    bool cameraOn;
    double internetSpeedMbps;
};

bool readYesNo(string text){
    char input;
    while(true){
        cout << text;
        cin >> input;

        if(input == 'Y' || input == 'y'){
            return true;
        }
        if(input == 'N' || input == 'n'){
            return false;
        }

        cout << "Please enter Y or N only!" << endl;
    }
}

string readString(string text){
    cin.ignore();
    string input;

    while(true){
        cout << text;
        getline(cin, input);

        if(!input.empty()){
            return input;
        }

        cout << "Input cannot be empty!" << endl;
    }
}

int readNum(string text, int min, int max){
    int input;
    while(true){
        cout << text;
        cin >> input;

        if(input >= min && input <= max){
            return input;
        }

        cout << "Please enter a number from " << min << " to " << max << "!" << endl;
    }
}

string generateCode(){
    const int length = 6;
    const string characters = "0123456789abcdefghijklmnopqrstuvwxyz";
    string code;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, characters.size()-1);

    for(int i=0; i < length; i++){
        code += characters[dist(gen)];
    }

    return code;
}

void schedule(Meeting &meeting, vector<Participant> &participants){
    bool choice;
    cout << endl << "= = = = Schedule a Meeting = = = =" << endl;

    if(meeting.scheduled){
        cout << "A Meeting has been scheduled" << endl;
        choice = readYesNo("Do you want to replace the current meeting? (Y/N): "); 
        if(!choice){
            return;
        }
        participants.clear();
    }

    meeting.topic = readString("Meeting Topic: ");
    meeting.duration = readNum("Meeting Duration in Minutes (1~150): ", 1, 150);
    meeting.totalParticipants = readNum("Total Participants (1~100): ", 1, 100);
    meeting.enableWaitingRoom = readYesNo("Enable Waiting Room?: ");
    
    meeting.id = generateCode();
    meeting.scheduled = true;

    cout << "= = = = Meeting Scheduled Successfully = = = =" << endl;
    cout << "Topic: " << meeting.topic << endl;
    cout << "Meeting ID: " << meeting.id << endl;
    cout << "Duration: " << meeting.duration << " minutes" << endl;
    cout << "Total Participants: " << meeting.totalParticipants << endl;
    cout << "Waiting Room: " << (meeting.enableWaitingRoom ? "Enabled" : "Disabled") << endl;
}

void mainMenu(){
    cout << "====================================" << endl;
    cout << "*      Zoom Meeting Assistant      *" << endl;
    cout << "====================================" << endl;
    cout << "*   1. Schedule a Meeting          *" << endl;
    cout << "*   2. Join a Meeting              *" << endl;
    cout << "*   3. Check Internet Readiness    *" << endl;
    cout << "*   4. Display Meeting Summary     *" << endl;
    cout << "*   5. Exit                        *" << endl;
    cout << "====================================" << endl;
}

int main(){
    Meeting meeting;
    vector<Participant> participants;

    int choice;
    mainMenu();
    choice = readNum("Enter your choice (1~5): ", 1, 5);

    switch (choice) {
        case 1:
            schedule(meeting, participants);
            break;
        
        case 2:
            // join meeting
            break;

        case 3:
            // check internet readiness
            break;

        case 4:
            // Meeting summary
            break;
        
        case 5:
            cout << endl << "Thank you for using the Zoom Meeting Assisteant!!";
            exit(0);
    }
}