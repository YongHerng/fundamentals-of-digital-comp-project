// Zoom Meeting Assistant

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <limits>
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
    bool micOn;
    bool cameraOn;
    double internetSpeed;
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
        cout << endl;
    }
}

string readString(string text){
    string input;

    while(true){
        cout << text;
        getline(cin, input);

        if(!input.empty()){
            return input;
        }

        cout << "Input cannot be empty!" << endl;
        cout << endl;
    }
}

int readNum(string text, int min, int max){
    int input;
    while(true){
        cout << text;

        if(cin >> input && input >= min && input <= max){
            return input;
        }

        cout << "Please enter a number from " << min << " to " << max << "!" << endl;
        cout << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float readFloat(string text, float min, float max){
    float input;
    while(true){
        cout << text;

        if(cin >> input && input >= min && input <= max){
            return input;
        }

        cout << "Please enter value from " << min << " to " << max << "!" << endl;
        cout << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

void scheduleMeeting(Meeting &meeting, vector<Participant> &participants){
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool choice;
    cout << endl << "= = = = Schedule a Meeting = = = =" << endl;

    if(meeting.scheduled){
        cout << "A Meeting has been scheduled" << endl;
        choice = readYesNo("Do you want to replace the current meeting? (Y/N): "); 
        if(!choice){
            cout << "= = = = = = = = = = = = = = = = = =" << endl;
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        participants.clear();
    }

    meeting.topic = readString("Meeting Topic: ");
    meeting.duration = readNum("Meeting Duration in Minutes (1~150): ", 1, 150);
    meeting.totalParticipants = readNum("Total Participants (1~100): ", 1, 100);
    meeting.enableWaitingRoom = readYesNo("Enable Waiting Room? [Y/N]: ");
    
    meeting.id = generateCode();
    meeting.scheduled = true;

    cout << endl;
    cout << "= = = = Meeting Scheduled Successfully = = = =" << endl;
    cout << "Topic: " << meeting.topic << endl;
    cout << "Meeting ID: " << meeting.id << endl;
    cout << "Duration: " << meeting.duration << " minutes" << endl;
    cout << "Total Participants: " << meeting.totalParticipants << endl;
    cout << "Waiting Room: " << (meeting.enableWaitingRoom ? "Enabled" : "Disabled") << endl;
    cout << "= = = = = = = = = = = = = = = = = = = = = = = =" << endl;
    cout << endl;
}

string checkConnection(float internetSpeed){
    if(internetSpeed < 0.5){
        return "Connection is unstable...";
    }
    if(internetSpeed < 1.5){
        return "Weak Connection. Turn off the camera and use audio only.";
    }
    if(internetSpeed < 5.0){
        return "Connection is stable for standard-quality video only.";
    }

    return "Connection is stable for high-quality video.";
}

float dataUsage(float internetSpeed, bool cameraOn, int duration){
    float bitrate;

    if(!cameraOn || internetSpeed < 1.5){
        bitrate = 0.1;
    } else if(internetSpeed < 5.0) {
        bitrate = 1.5;
    } else {
        bitrate = 3.0;
    }

    float usage = bitrate * duration * 60 / 8;

    return usage / 1024;
}

void joinMeeting(Meeting meeting, vector<Participant> &participantsList){
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string meetingId;
    Participant participant;
    cout << endl << "= = = = Join a Meeting = = = =" << endl;
    
    if(!meeting.scheduled){
        cout << "Currently no meeting has been scheduled yet!" << endl;
        cout << endl;
        return;
    }

    if(participantsList.size() >= static_cast<size_t>(meeting.totalParticipants)){
        cout << "Meeting room is full!" << endl;
        cout << endl;
        return;
    }

    do{
        meetingId = readString("Enter Meeting ID: ");
        if(meetingId != meeting.id){
            cout << "Invalid Meeting ID!" << endl;
        }
    }while(meetingId != meeting.id);

    participant.name = readString("Participant Name: ");
    participant.micOn = readYesNo("Turn on the Microphone? [Y/N]: ");
    participant.cameraOn = readYesNo("Turn on the Camera? [Y/N]: ");
    participant.internetSpeed = readFloat("Internet Speed (Mbps) (0.1~1000): ", 0.1, 1000);

    participantsList.push_back(participant);

    if(meeting.enableWaitingRoom){
        cout << endl;
        cout << participant.name << " has been placed in the meeting room." << endl;
        cout << "The host has admitted the participant!" << endl;
    }

    cout << endl;
    cout << "= = = = = = = Meeting Info = = = = = = =" << endl;
    cout << participant.name << " joined the meeting!" << endl;
    cout << "Connection Result: " << checkConnection(participant.internetSpeed) << endl;
    float usage = dataUsage(participant.internetSpeed, participant.cameraOn, meeting.duration); 
    cout << "Estimated Data Usage: " << fixed << setprecision(2) << usage << " GB" << endl;
    cout << "= = = = = = = = = = = = = = = = = = = = =" << endl;
    cout << endl;
}

void checkInternet(){
    cout << endl << "= = = = Check Internet Readiness = = = =" << endl;

    float internetSpeed = readFloat("Internet speed (Mbps) (0.1~1000): ", 0.1, 1000);
    bool cameraOn = readYesNo("Do you intend to use camera? [Y/N]: ");
    int duration = readNum("Planned meeting duration in minutes: ", 1, 100);

    cout << endl;
    cout << "= = = = = = = Internet Readiness = = = = = = =" << endl;
    cout << "Connection Result: " << checkConnection(internetSpeed) << endl;
    float usage = dataUsage(internetSpeed, cameraOn, duration);
    cout << "Estimated Data Usage: " << fixed << setprecision(2) << usage << " GB" << endl;
    cout << "= = = = = = = = = = = = = = = = = = = = = = = =" << endl;
    cout << endl;
}

void meetingSummary(Meeting meeting, vector<Participant> participantsList) {
    cout << endl << "= = = = Meeting Summary = = = =" << endl;
    
    if(!meeting.scheduled){
        cout << "Currently no meeting has been scheduled yet!" << endl;
        return;
    }

    cout << "Meeting Topic: " << meeting.topic << endl;
    cout << "Meeting ID: " << meeting.id << endl;
    cout << "Duration: " << meeting.duration << " minutes" << endl;
    cout << "Joined Participant(s): " << participantsList.size() << " out of " << meeting.totalParticipants << endl;
    cout << "Waiting Room: " << (meeting.enableWaitingRoom ? "Enabled" : "Disabled") << endl;

    if(participantsList.empty()){
        cout << "No one have joined the meeting yet..." << endl;
        return;
    }

    cout << endl << "Participant(s) Details" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << left 
         << setw(15) << "Name" 
         << setw(12) << "Microphone" 
         << setw(10) << "Camera" 
         << setw(15) << "Internet Speed" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    for(Participant participant : participantsList){
        cout << left 
             << setw(15) << participant.name 
             << setw(12) << (participant.micOn ? "On" : "Off") 
             << setw(10) << (participant.cameraOn ? "On" : "Off") 
             << fixed << setprecision(2) << participant.internetSpeed << " Mbps" << endl;
    }
    cout << "---------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" << endl;
    cout << endl;
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
    vector<Participant> participantsList;

    int choice;
    while(true){
        mainMenu();
        choice = readNum("Enter your choice (1~5): ", 1, 5);

        switch (choice) {
            case 1:
                scheduleMeeting(meeting, participantsList);
                break;
        
            case 2:
                joinMeeting(meeting, participantsList);
                break;

            case 3:
                checkInternet();
                break;

            case 4:
                meetingSummary(meeting, participantsList);
                break;
        
            case 5:
                cout << endl << "Thank you for using the Zoom Meeting Assistant!!" << endl;
                return 0;
        }
    }
}