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
        int fileCount = 1; // 文件計數器
        int valueCount = 0; // 當前文件的value計數器

        for (size_t i = 0; i < values.size(); ++i)
        {
            // 每200個value或開始一個新的key時，創建一個新文件
            if (valueCount == 0 || valueCount % 200 == 0)
            {
                // 構造檔案路徑和名稱
                stringstream ss;
                ss << "./course_student/" << key << "_" << setw(3) << setfill('0') << fileCount << ".txt";
                string filePath = ss.str();

                // 打開檔案準備寫入
                ofstream outFile(filePath);
                if (!outFile)
                {
                    cerr << "Failed to open file for writing: " << filePath << endl;
                    break; // 如果無法打開文件，則跳出循環
                }

                // 寫入當前批次的value，直到達到200個或所有value寫完
                for (; i < values.size() && valueCount < 200; ++i, ++valueCount)
                {
                    outFile << values[i] << endl;
                }

                // 關閉當前文件
                outFile.close();

                // 更新文件計數器並重置value計數器
                ++fileCount;
                valueCount = 0;

                // 如果當前批次已經寫完，需要將循環變量i回退一個位置，因為for循環會再次進行i++
                if (i < values.size()) --i;
            }
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
                string student_id, course_id, course_name;
                getline(ss, student_id, ','); // 第一個元素是 student_id
                getline(ss, course_id, ',');  // 第二個元素是 course_id
                // 無需提取 course_name，除非之後需要使用
                // getline(ss, course_name, ','); // 第三個元素是 course_name（如果需要的話）

                stringstream positionStream;            // 創建一個 stringstream 對象
                positionStream << x << "," << count;    // 將 x 和 count 的值，以及一個逗號分隔符寫入到 stringstream 中
                string position = positionStream.str(); // 從 stringstream 對象中獲取格式化後的字符串
                data[course_id].push_back(position);    // 將整行資料存入 data[course_id]
            }
        }
        in.close();
        x++;
    }
    saveData();
    return 0;
}