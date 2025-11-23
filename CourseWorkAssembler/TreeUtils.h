#pragma once
#include "Structures.h"

void PrintHeader();

// Основные функции
void AddNode(TreeNode*& root, Train data);
void PrintTree(TreeNode* root); // Прямой обход
void SearchBySoldRange(TreeNode* root, int minVal, int maxVal);

// Сортировка (через динамический массив)
void SortAndPrint(TreeNode* root);

// Индивидуальные задания
void BuyTicketTask(TreeNode* root);
void FilterTrainsTask(TreeNode* root);

// Вспомогательные функции (для ручного управления памятью)
int CountNodes(TreeNode* root);
void TreeToArray(TreeNode* root, Train* arr, int& index);