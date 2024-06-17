#include <iostream>
#include <fstream>
#include <string>
#include "dirent.h"  // Include dirent.h for directory operations

using namespace std;

struct TreeNode {
    string fileName;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string name) : fileName(name), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    TreeNode* root;

    BinarySearchTree() : root(nullptr) {}

   void insert(string name) {
        if (!root) {
            root = new TreeNode(name);
            return;
        }
        
        TreeNode* current = root;
        while (true) {
            if (name < current->fileName) {
                if (current->left) {
                    current = current->left;
                } else {
                    current->left = new TreeNode(name);
                    break;
                }
            } else if (name > current->fileName) {
                if (current->right) {
                    current = current->right;
                } else {
                    current->right = new TreeNode(name);
                    break;
                }
            } else {
                break;
            }
        }
    }

    TreeNode* insertRecursive(TreeNode* node, string name) {
        if (node == nullptr) {
            return new TreeNode(name);
        }
        if (name < node->fileName) {
            node->left = insertRecursive(node->left, name);
        } else if (name > node->fileName) {
            node->right = insertRecursive(node->right, name);
        }
        return node;
    }

    TreeNode* search(string name) {
        return searchRecursive(root, name);
    }

    TreeNode* searchRecursive(TreeNode* node, string name) {
        cout << "Searching for: " << name << endl; // Debug output
        cout << "Now searching in: " << node->fileName << endl; // Debug output
        if (node == nullptr) {
            cout << "Search hit null node, not found." << endl; // Debug output
            return node;
        }
        if (node->fileName == name) {
            return node;
        }
        if (name < node->fileName) {
            return searchRecursive(node->left, name);
        } else {
            return searchRecursive(node->right, name);
        }
    }
};

void populateTreeFromDirectory(BinarySearchTree& bst, const string& directoryPath) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directoryPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string filename = ent->d_name;
            if (filename.find(".txt") != string::npos) {
                bst.insert(filename);
                // cout << "Inserted: " << filename << endl; // Debug output
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }
}


void displayFileContents(const string& filePath) {
    cout << filePath << endl;
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

//test Tree
void inorderTraversal(TreeNode* node) {
    if (node == nullptr) return;
    inorderTraversal(node->left); // 訪問左子樹
    cout << node->fileName << endl; // 輸出當前節點存儲的文件名
    inorderTraversal(node->right); // 訪問右子樹
}

void displayAllFiles(BinarySearchTree& bst) {
    cout << "All files in the binary search tree:" << endl;
    inorderTraversal(bst.root);
}

int main() {
    BinarySearchTree bst;
    string directoryPath = "./selected_course/";
    populateTreeFromDirectory(bst, directoryPath);
    // displayAllFiles(bst); // 顯示所有文件名
    //D053003133.txt
    while (true) {
        string searchFile;
        cout << "Enter the name of the .txt file to search: ";
        cin >> searchFile;
        if (searchFile == "exit") {
            cout << "Exiting..." << endl;
            break;
        }
        cout << "Searching for: " << searchFile << endl; // Debug output

        TreeNode* result = bst.search(searchFile);
        if (result) {
            cout << searchFile << " found in the binary search tree." << endl;
            displayFileContents(directoryPath + searchFile);
        } else {
            cout << searchFile << " not found in the binary search tree." << endl;
        }
    }
    return 0;
}
