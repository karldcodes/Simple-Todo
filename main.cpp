#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <conio.h>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayTasks(const vector<string>& tasks){
    clearScreen();

    cout << "==== TASKS ====" << endl << endl;

    if (tasks.empty()) {
        cout << "No tasks yet." << endl << endl;
        return;
    }

    for (int i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i] << endl;
    }

    cout << endl;
}

void showCommandList(){
    cout << "Enter command: (d)elete task, (a)dd task, (q)uit" << endl;
}

int main() {
    vector<string> tasks;

    displayTasks(tasks);
    showCommandList();

    while(true)
    {
        if(_kbhit())
        {
            char command = _getch();

            if (command == 'a')
            {
                // Add task
                string sentence;
                cout << "Enter a todo: ";
                getline(cin, sentence);
                tasks.push_back(sentence);
            }

            if (command == 'd')
            {
                // Remove a task
                int taskNumber;
                cout << "Enter task number to remove: ";
                
                if (!(cin >> taskNumber))
                {
                    cin.clear(); // Clear the error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (taskNumber >= 1 && taskNumber <= tasks.size()) {
                        tasks.erase(tasks.begin() + taskNumber - 1);
                    }    
                }
            }

            if (command == 'q'){
                break;
            }

            displayTasks(tasks);
            showCommandList();
        }
    }

    return 0;
}
