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
    stringstream ss;
    ss << "./course_student/" << stu_id << ".txt";
    string filePath = ss.str();
    in.open(filePath.c_str());
    if (!in)
    {
        cout << "The course ID does not exist." << endl;
        return;
    }
    vector<pair<int,int>> poslist;
    string pos;
    while(getline(in, pos))
    {
        stringstream posStream(pos); // 將字串pos轉換為流
        string segment;
        vector<int> seglist;

        // 使用逗號作為分隔符從流中讀取數字
        while(getline(posStream, segment, ','))
        {
            seglist.push_back(stoi(segment)); // 將字串轉換為int並儲存到向量中
        }

        // 假設seglist中現在有兩個元素，分別儲存到兩個不同的int變數中
        int firstNumber = seglist[0];
        int secondNumber = seglist[1];
        // 現在你可以使用firstNumber和secondNumber進行後續操作
        poslist.push_back(make_pair(firstNumber, secondNumber));
    }
    in.close();
    for (auto &pair : poslist)
    {
        stringstream search_id;
        search_id << "./data_big5/" << setw(4) << setfill('0') << pair.first;
        string search_locate = search_id.str();
        in.open(search_locate.c_str());
        string temp_str;
        for(int i = 0;i < pair.second;i++)
        {
            getline(in, temp_str);
        }
        in.close();
        cout << temp_str << endl;
    }
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