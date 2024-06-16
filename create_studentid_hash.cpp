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
map<string, vector<string>> data;
void saveData()
{
    for (const auto &pair : data)
    {
        const string &key = pair.first;
        // 檢查key是否為空
        if (key.empty())
        {
            continue; // 跳過這個迴圈的迭代
        }

        const vector<string> &values = pair.second;

        // 構造檔案路徑和名稱
        stringstream ss;
        ss << "./selected_course/" << key << ".txt";
        string filePath = ss.str();

        // 打開檔案準備寫入
        ofstream outFile(filePath);
        if (!outFile)
        {
            cerr << "Failed to open file for writing: " << filePath << endl;
            continue; // 處理下一個檔案
        }
        // 寫入數據
        for (const string &value : values)
        {
            outFile << value << endl;
        }
        // 關閉檔案
        outFile.close();
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
        datacounter++;
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
            while (getline(in, s)) // 讀取一行
            {
                count++;
                // 透過,分割字串
                stringstream ss(s); // 使用 stringstream 來處理字符串
                string student_id;
                getline(ss, student_id, ',');           // 使用 ',' 作為分隔符來提取 student_id
                stringstream positionStream;            // 創建一個 stringstream 對象
                positionStream << x << "," << count;    // 將 x 和 count 的值，以及一個逗號分隔符寫入到 stringstream 中
                string position = positionStream.str(); // 從 stringstream 對象中獲取格式化後的字符串
                data[student_id].push_back(position);   // 將整行資料存入 date[student_id]
            }
        }
        in.close();
        x++;
    }
    saveData();
    return 0;
}