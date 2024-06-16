#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <iomanip>
#include <io.h> // or <unistd.h> for POSIX systems

using namespace std;

void search(size_t hashValue) {
    stringstream ss;
    ss << "./selected_courseName/" << hashValue;
    string filePath = ss.str();
    cout << "." << endl;
    // Check if directory exists
    if (_access(filePath.c_str(), 0) == -1) {
        cout << "The course name does not exist." << endl;
        return;
    }

    vector<pair<int, int>> poslist;
    int fileIndex = 1;
    while (true) {
        stringstream fileStream;
        fileStream << filePath << "/" << setfill('0') << setw(4) << fileIndex;
        string positionFilePath = fileStream.str();
        cout <<"       " << positionFilePath << endl;

        // if (_access(positionFilePath.c_str(), 0) == -1) {
        //     cout << "end find" << endl;
        //     break; // Exit the loop if the file does not exist
        // }

        ifstream in(positionFilePath);
        if (!in.is_open()) {
            //cerr << "Failed to open positions file: " << positionFilePath << endl;
            break;;
        }

        string pos;
        while (getline(in, pos)) {
            stringstream posStream(pos);
            string segment;
            vector<int> seglist;

            while (getline(posStream, segment, ',')) {
                seglist.push_back(stoi(segment));
            }

            if (seglist.size() >= 2) {
                int firstNumber = seglist[0];
                int secondNumber = seglist[1];
                poslist.push_back(make_pair(firstNumber, secondNumber));
            }
        }
        in.close();
        fileIndex++;
    }

    cout << "output:" << endl;
    int count = 0;

    // Search and retrieve data from "data_big5" based on positions
    for (auto &pair : poslist) {
        count++;
        stringstream search_id;
        search_id << "./data_big5/" << setw(4) << setfill('0') << pair.first;
        string search_locate = search_id.str();
        ifstream in(search_locate.c_str());
        if (!in.is_open()) {
            cerr << "Failed to open data file: " << search_locate << endl;
            continue;
        }
        string temp_str;
        for (int i = 0; i < pair.second; i++) {
            getline(in, temp_str);
        }
        in.close();
        cout << temp_str << endl;
    }

    cout << "total :" << count << endl;
}

int main() {
    while(1) {
        string course_name;
        cout << "Please enter the course name: ";
        cin >> course_name;
        // Generate hash value from the key
        size_t hashValue = hash<string>{}(course_name);
        search(hashValue);
        cout << "Do you want to search for another course name? (Y/N): ";
        char choice;
        cin >> choice;
        if(choice == 'N' || choice == 'n') {
            break;
        } else {
            system("cls");
            continue;
        }
    }
    return 0;
}
