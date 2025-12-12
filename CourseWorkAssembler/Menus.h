#pragma once
#pragma once
#include "Structures.h"
#include "Authorization.h"

void UserModule(TreeNode*& root);
void AdminModule(TreeNode*& root);
void AdminAccountsMenu();
void AdminDataMenu(TreeNode*& root);
void AdminEditMode(TreeNode*& root);
void AdminProcessMode(TreeNode* root);
void UserDataMenu(TreeNode*& root);