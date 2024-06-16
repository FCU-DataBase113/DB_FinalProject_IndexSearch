#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <set>
using namespace std;
ifstream in;
void search(string stu_id)
{
    int fileIndex = 1; // 從1開始計數
    bool fileExists = true; // 假設文件存在
    vector<string> allLines; // 用於儲存所有temp_str的vector
    int std_nums = 0;
    while (fileExists)
    {
        stringstream ss;
        ss << "./course_student/" << stu_id << "_" << setw(3) << setfill('0') << fileIndex << ".txt";
        string filePath = ss.str();
        ifstream in(filePath.c_str());
        if (!in)
        {
            fileExists = false; // 如果文件不存在，設置fileExists為false並退出循環
            if (fileIndex == 1) // 如果連第一個文件都不存在，則輸出錯誤信息
            {
                cout << "The course ID does not exist." << endl;
            }
            break;
        }
        vector<pair<int,int>> poslist;
        string pos;
        while(getline(in, pos))
        {
            stringstream posStream(pos);
            string segment;
            vector<int> seglist;

            while(getline(posStream, segment, ','))
            {
                seglist.push_back(stoi(segment));
            }

            int firstNumber = seglist[0];
            int secondNumber = seglist[1];
            poslist.push_back(make_pair(firstNumber, secondNumber));
        }
        in.close();
        for (auto &pair : poslist)
        {
            stringstream search_id;
            search_id << "./data_big5/" << setw(4) << setfill('0') << pair.first;
            string search_locate = search_id.str();

            ifstream in(search_locate.c_str());
            string temp_str;
            for(int i = 0; i < pair.second; i++)
            {
                getline(in, temp_str);
            }
            in.close();
            allLines.push_back(temp_str); // 將讀取到的字符串添加到vector中
            std_nums++;
        }
        fileIndex++; // 嘗試下一個文件編號
    }
    sort(allLines.begin(), allLines.end()); // 對所有字符串進行排序
    for (const auto &line : allLines)
    {
        cout << line << endl; // 輸出排序後的每個字符串
    }
    cout << "Total number of students: " << std_nums << endl;
}
int main() 
{
    while(1)
    {
        string stu_id;
        cout << "Please enter the course ID: ";
        cin >> stu_id;
        search(stu_id);
        cout << "Do you want to search for another course? (Y/N): ";
        char choice;
        cin >> choice;
        if(choice == 'N' || choice == 'n')
        {
            break;
        }
        else
        {
            system("cls");
            continue;
        }
    }
    return 0;
}