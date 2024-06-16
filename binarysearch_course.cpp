#include <iostream>
#include <fstream>
#include <string>
#include "dirent.h"  // Include dirent.h for directory operations

using namespace std;

struct Index {
    int course_id;
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
        if (!root) {
            root = new TreeNode(idx);
            return;
        }

        TreeNode* current = root;
        while (true) {
            if (idx.course_id < current->index.course_id) {
                if (current->left) {
                    current = current->left;
                } else {
                    current->left = new TreeNode(idx);
                    break;
                }
            } else if (idx.course_id > current->index.course_id) {
                if (current->right) {
                    current = current->right;
                } else {
                    current->right = new TreeNode(idx);
                    break;
                }
            } else {
                // course_id 相同，不需要插入
                break;
            }
        }
    }

    TreeNode* search(int course_id) {
        return searchRecursive(root, course_id);
    }

    TreeNode* searchRecursive(TreeNode* node, int course_id) {
        if (node == nullptr || node->index.course_id == course_id) {
            return node;
        }
        if (course_id < node->index.course_id) {
            return searchRecursive(node->left, course_id);
        } else {
            return searchRecursive(node->right, course_id);
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
                ifstream file(directoryPath + filename);
                if (file.is_open()) {
                    string student_id;
                    int course_id;
                    string course_name;
                    file >> student_id >> course_id;
                    file.ignore(); // Ignore the space between course_id and course_name
                    getline(file, course_name);
                    Index idx = {course_id, filename};
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

void inorderTraversal(TreeNode* node) {
    if (node == nullptr) return;
    inorderTraversal(node->left); // 訪問左子樹
    cout << "Course ID: " << node->index.course_id << ", File: " << node->index.fileName << endl; // 輸出當前節點存儲的文件名
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

    while (true) {
        int searchCourseId;
        cout << "Enter the course ID to search: ";
        cin >> searchCourseId;
        if (searchCourseId == -1) {
            cout << "Exiting..." << endl;
            break;
        }

        TreeNode* result = bst.search(searchCourseId);
        if (result) {
            cout << "Course ID " << searchCourseId << " found in the binary search tree." << endl;
            displayFileContents(directoryPath + result->index.fileName);
        } else {
            cout << "Course ID " << searchCourseId << " not found in the binary search tree." << endl;
        }
    }
    return 0;
}
