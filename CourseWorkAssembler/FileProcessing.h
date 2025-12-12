#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include "TreeUtils.h"
#include "string"
#include "Structures.h"
#include "Authorization.h"

static const char* DAT_FILE_NAME = "AllData.bin";
static const char* FILE_NAME = "AllPeople.txt";

void SaveArrayToFile(UserAndAdmin* arr, int count);
UserAndAdmin* LoadUsersToArray(int& count);
void OpenAndSaveTreeToFile(TreeNode* node);
void SaveTreeToFile(TreeNode* node, ofstream& file);
void SaveNodeToFile(TreeNode* node, ofstream& file);
void InsertNode(TreeNode*& root, Train data);
TreeNode* LoadTreeFromFile();


