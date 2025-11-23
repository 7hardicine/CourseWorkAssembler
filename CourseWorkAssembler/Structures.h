#pragma once
#include <string>
using namespace std;

struct Train {
    int number;
    string destination;
    string depDate;
    int depH, depM;
    int arrH, arrM;
    double price;
    int ticketsLeft;
    int ticketsSold;
};

struct TreeNode {
    Train data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(Train t) : data(t), left(nullptr), right(nullptr) {}
};