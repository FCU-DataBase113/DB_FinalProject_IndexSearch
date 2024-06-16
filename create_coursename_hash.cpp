#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <windows.h>
#include <tchar.h>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <direct.h>
using namespace std;
map<string, vector<string>> data;

// bool IsFileExists(const string &file_name) {
//   ifstream fin(file_name);
//   if (fin) {
//     return true;
//   } else {
//     //cout << file_name << " is not exist" << endl;
//     return false;
//   }
//   return true;
// }

// Function to get file size in bytes
size_t getFileSize(const string& fileName) {
    ifstream file(fileName, ios::binary | ios::ate);
    if (!file.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return 0; // Return 0 on error
    }
    size_t size = file.tellg(); // Get file size
    file.close();
    return size;
}

void saveData() {
    for (const auto& pair : data) {
        const string& key = pair.first;
        const vector<string>& values = pair.second;

        // Skip empty keys
        if (key.empty()) {
            cerr << "Key is empty, skipping..." << endl;
            continue;
        }

        // Generate hash value from the key
        size_t hashValue = hash<string>{}(key);

        // Construct directory path
        stringstream ss;
        ss << "./selected_courseName/" << hashValue;
        string filePath = ss.str();

        // Create directory if it doesn't exist
        if (_mkdir(filePath.c_str()) != 0) {
            cerr << "Creating indexing for: " << filePath << endl;
            // Skip to next iteration if directory creation fails
        }

        // Process each value for writing
        int counter = 1;
        for (const string& value : values) {
            stringstream sss;
            sss << filePath << "/" << setw(4) << setfill('0') << counter;
            string fileName = sss.str();

            // Open file for appending
            ofstream outFile(fileName, ios::app);
            if (!outFile.is_open()) {
                cerr << "Creating file for writing: " << fileName << endl;
                continue; // Skip to next file if opening fails
            }
            //-----------------------------------------------------------------
            // cout << "log :: " << "Creating file for writing: " << fileName << endl;
            //-----------------------------------------------------------------
            // Write value to file
            outFile << value << endl;

            // Check file size and increment counter if necessary
            while (getFileSize(fileName) >= 2000) {
                counter++;
                sss.str("");
                sss << filePath << "/" << setw(4) << setfill('0') << counter;
                fileName = sss.str();
                outFile.close();
                outFile.open(fileName, ios::app);
                if (!outFile.is_open()) {
                    cerr << "Failed to open file for writing: " << fileName << endl;
                    break; // Exit loop if opening fails
                }
            }

            outFile.close(); // Close the file after writing
        }
    }
}

int main()
{
    ifstream in;
    int datacounter = 1;
    string locate = "./data_big5/";
    int x = 1;
    while (x < 467)
    {
        stringstream ss;
        ss << locate << setw(4) << setfill('0') << datacounter;
        string data_locate = ss.str();
        printf("locate: %s\n", data_locate.c_str());
        datacounter++;

        // ==============================================

        in.open(data_locate.c_str());
        if (in.fail())
        {
            cout << "input file opening failed\n";
            break;
        }
        else
        {
            string s;
            in >> s;
            int count = 0;
            while (getline(in, s)) 
            {
                count++;
                
                stringstream ss(s); 
                string course_name;
                getline(ss, course_name, ','); 
                getline(ss, course_name, ',');
                getline(ss, course_name, ',');
                stringstream positionStream; 
                positionStream << x << "," << count; 
                string position = positionStream.str(); 
                //cout << course_name << position << endl;
                data[course_name].push_back(position); 
            }
        }
        in.close();
        x++;
    }
    // ==============================================
    saveData();
    return 0;
}