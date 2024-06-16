
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
ifstream temp;
void search(string stu_id)
{
    stringstream ss;
    ss << "./selected_course/" << stu_id << ".txt";
    string filePath = ss.str();
    in.open(filePath.c_str());
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
        stringstream search_id;
        search_id << "./data_big5/" << setw(4) << setfill('0') << firstNumber;
        string search_locate = search_id.str();
        temp.open(search_locate.c_str());
        string temp_str;
        for(int i = 0;i < secondNumber;i++)
        {
            getline(temp, temp_str);
        }
        temp.close();
        cout << temp_str << endl;
    }
}
int main() 
{
    search("D000003506");
    return 0;
}