// Zoom Meeting Assistant

#include <iostream>
using namespace std;

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
    int choice;
    mainMenu();
    do{
        cout << "Enter your choice (1~5): ";
        cin >> choice;
        if(choice >= 6 || choice < 1){
            cout << "Please enter a number among 1 to 5!" << endl;
            cout << endl;
        }
    } while(choice >= 6 || choice < 1);
}