#include <iostream>
#include "FileProcessing.h"

void SaveArrayToFile(UserAndAdmin* arr, int count) 
{
    ofstream file(FILE_NAME);
    for (int i = 0; i < count; i++) {
        file << arr[i].login << ";" << arr[i].password << ";" << arr[i].role;
        if (i < count - 1) file << endl;
    }
    file.close();
}

UserAndAdmin* LoadUsersToArray(int& count) {
    count = GetUsersCount();
    if (count == 0) return nullptr;

    UserAndAdmin* arr = new UserAndAdmin[count];
    ifstream file(FILE_NAME);
    string line;
    int i = 0;
    while (getline(file, line) && i < count) {
        if (line.empty()) continue;
        size_t p1 = line.find(';');
        size_t p2 = line.find(';', p1 + 1);
        if (p1 == string::npos || p2 == string::npos) continue;

        arr[i].login = line.substr(0, p1);
        arr[i].password = line.substr(p1 + 1, p2 - p1 - 1);
        arr[i].role = line.substr(p2 + 1);
        i++;
    }
    file.close();
    return arr;
}

void OpenAndSaveTreeToFile(TreeNode* node)
{
    ofstream file(DAT_FILE_NAME);
    SaveTreeToFile(node, file);
    file.close();
}

void SaveTreeToFile(TreeNode* node, ofstream& file)
{
    if (!node) return;
    SaveNodeToFile(node, file);
    SaveTreeToFile(node->left, file);
    SaveTreeToFile(node->right, file);
}

void InsertNode(TreeNode*& root, Train data) {
    if (!root) {
        root = new TreeNode(data);
        return;
    }
    if (data.number < root->data.number) {
        InsertNode(root->left, data);
    }
    else {
        InsertNode(root->right, data);
    }
}

TreeNode* LoadTreeFromFile() {
    ifstream file(DAT_FILE_NAME);
    if (!file.is_open()) {
        return nullptr;
    }

    TreeNode* root = nullptr;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string segment;
        Train t;
        if (!getline(ss, segment, ';')) continue;
        t.number = stoi(segment);
        if (!getline(ss, segment, ';')) continue;
        t.destination = segment;
        if (!getline(ss, segment, ';')) continue;
        t.depDate = segment;
        if (!getline(ss, segment, ';')) continue;
        t.depH = stoi(segment);
        if (!getline(ss, segment, ';')) continue;
        t.depM = stoi(segment);
        if (!getline(ss, segment, ';')) continue;
        t.arrH = stoi(segment);
        if (!getline(ss, segment, ';')) continue;
        t.arrM = stoi(segment);
        if (!getline(ss, segment, ';')) continue;
        t.price = stod(segment);
        if (!getline(ss, segment, ';')) continue;
        t.ticketsLeft = stoi(segment);
        if (!getline(ss, segment, ';')) continue;
        t.ticketsSold = stoi(segment);

        InsertNode(root, t);
    }

    file.close();
    return root;
}

void SaveNodeToFile(TreeNode* node, ofstream& file)
{
    file << node->data.number << ";" << node->data.destination << ";"
        << node->data.depDate << ";" << node->data.depH << ";"
        << node->data.depM << ";" << node->data.arrH << ";"
        << node->data.arrM << ";" << node->data.price << ";"
        << node->data.ticketsLeft << ";" << node->data.ticketsSold << endl;
}
