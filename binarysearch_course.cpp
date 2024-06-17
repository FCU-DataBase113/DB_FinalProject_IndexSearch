#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "dirent.h"  // Include dirent.h for directory operations

using namespace std;

struct Index {
    int course_id;
    string fileNamePrefix;
    string fileName;
};

struct TreeNode {
    Index index;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Index idx) : index(idx), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    TreeNode* root;

    BinarySearchTree() : root(nullptr) {}

    void insert(Index idx) {
        TreeNode* newNode = new TreeNode(idx);
        if (!root) {
            root = newNode;
            return;
        }

        TreeNode* current = root;
        while (true) {
            if (idx.fileName < current->index.fileName) {
                if (current->left) {
                    current = current->left;
                } else {
                    current->left = newNode;
                    break;
                }
            } else if (idx.fileName > current->index.fileName) {
                if (current->right) {
                    current = current->right;
                } else {
                    current->right = newNode;
                    break;
                }
            } else {
                break;
            }
        }
    }

    void searchByPrefix(TreeNode* node, const string& prefix) {
        if (!node) return;
        searchByPrefix(node->left, prefix);
        // 檢查當前節點的文件名前綴是否與輸入的前綴匹配
        if (node->index.fileName.substr(0, prefix.length()) == prefix) {
            displayFileContents("./course_student/" + node->index.fileName);
        }
        searchByPrefix(node->right, prefix);
    }

    void displayFileContents(const string& filePath) {
        ifstream file(filePath);
        if (file.is_open()) {
            cout << "Contents of " << filePath << ":" << endl;
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "Failed to open file: " << filePath << endl;
        }
    }
};



void populateTreeFromDirectory(BinarySearchTree& bst, const string& directoryPath) {
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(directoryPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string filename = ent->d_name;
            if (filename.find(".txt") != string::npos) {
                string prefix = filename.substr(0, filename.find('_'));
                ifstream file(directoryPath + filename);
                if (file.is_open()) {
                    int course_id;
                    file >> course_id;
                    Index idx = {course_id, prefix, filename};
                    bst.insert(idx);
                    file.close();
                }
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }
}
//testTree
void inorderTraversal(TreeNode* node) {
    if (node == nullptr) return;
    inorderTraversal(node->left); // 遍歷左子樹
    cout << "Course ID: " << node->index.course_id << ", Prefix: " << node->index.fileNamePrefix << ", File Name: " << node->index.fileName << endl; // 輸出當前節點存儲的資料
    inorderTraversal(node->right); // 遍歷右子樹
}

void displayAllTreeData(BinarySearchTree& bst) {
    cout << "All data in the binary search tree:" << endl;
    inorderTraversal(bst.root);
}

int main() {
    BinarySearchTree bst;
    string directoryPath = "./course_student/";
    populateTreeFromDirectory(bst, directoryPath);
        displayAllTreeData(bst);

    while (true) {
        string searchPrefix;
        cout << "Enter the file prefix to search: ";
        cin >> searchPrefix;
        if (searchPrefix == "exit") {
            cout << "Exiting..." << endl;
            break;
        }

        cout << "Searching for files with prefix " << searchPrefix << ":" << endl;
        bst.searchByPrefix(bst.root, searchPrefix);
    }
    return 0;
}
