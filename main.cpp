#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <fstream>

using namespace std;

const string file_name = "todo.txt";

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

void write_tasks_to_file(const vector<string>& tasks){
    ofstream myfile (file_name);
    if (myfile.is_open())
    {
        for (int i = 0; i < tasks.size(); i++) {
            myfile << tasks[i] << endl;
        }
        myfile.close();
    }
}

int main() {
    vector<string> tasks;

    std::ifstream file(file_name);

    if (file.is_open()){
        string line;
        while (std::getline (file, line)) {
            tasks.push_back(line);
        }
        file.close();
    }

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

            write_tasks_to_file(tasks);
            displayTasks(tasks);
            showCommandList();
        }
    }

    return 0;
}
