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

float readFloat(string text, float min, float max){
    float input;
    while(true){
        cout << text;
        cin >> input;

        if(input >= min && input <= max){
            return input;
        }

        cout << "Please enter value from " << min << " to " << max << "!" << endl;
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
            return;
        }
        participants.clear();
    }

    meeting.topic = readString("Meeting Topic: ");
    meeting.duration = readNum("Meeting Duration in Minutes (1~150): ", 1, 150);
    meeting.totalParticipants = readNum("Total Participants (1~100): ", 1, 100);
    meeting.enableWaitingRoom = readYesNo("Enable Waiting Room? [Y/N]: ");
    
    meeting.id = generateCode();
    meeting.scheduled = true;

    cout << "= = = = Meeting Scheduled Successfully = = = =" << endl;
    cout << "Topic: " << meeting.topic << endl;
    cout << "Meeting ID: " << meeting.id << endl;
    cout << "Duration: " << meeting.duration << " minutes" << endl;
    cout << "Total Participants: " << meeting.totalParticipants << endl;
    cout << "Waiting Room: " << (meeting.enableWaitingRoom ? "Enabled" : "Disabled") << endl;
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
        return;
    }

    if(participantsList.size() >= meeting.totalParticipants){
        cout << "Meeting room is full!" << endl;
        return;
    }

    do{
        meetingId = readString("Enter Meeting ID: ");
        if(meetingId != meeting.id){
            cout << "Invalid Meeting ID!" << endl;
        }
    }while(meetingId != meeting.id);

    participant.name = readString("Participant name: ");
    participant.micOn = readYesNo("Turn on the microphone? [Y/N]: ");
    participant.cameraOn = readYesNo("Turn on the camera? [Y/N]: ");
    participant.internetSpeed = readFloat("Internet speed (Mbps) (0.1~1000): ", 0.1, 1000);

    participantsList.push_back(participant);

    cout << endl << "= = = = Meeting Info = = = =" << endl;
    cout << participant.name << " joined the meeting!" << endl;
    cout << "Connection Result: " << checkConnection(participant.internetSpeed) << endl;
    float usage = dataUsage(participant.internetSpeed, participant.cameraOn, meeting.duration); 
    cout << "Estimated Data Usage: " << usage << " GB" << endl;
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
}