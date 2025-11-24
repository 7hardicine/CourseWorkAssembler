#pragma once
#include "Structures.h"

void PrintHeader();
void PrintTrain(const Train& t);
void AddNode(TreeNode*& root, Train data);
void PrintTree(TreeNode* root);

// Новые функции
TreeNode* DeleteNode(TreeNode* root, int num);
void EditTrainData(TreeNode* node);
TreeNode* FindByNumber(TreeNode* root, int num);

void SearchBySoldRange(TreeNode* root, int minVal, int maxVal);
void SortAndPrint(TreeNode* root);
void BuyTicketTask(TreeNode* root);
void FilterTrainsTask(TreeNode* root);