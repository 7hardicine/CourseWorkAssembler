#include "Authorization.h"
#include "Menus.h"
#include "TreeUtils.h"
#include "FileProcessing.h"
#include <iostream>
#include <Windows.h> 

using namespace std;

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    UserAndAdmin currentUser;
    
    bool isRunning = true;

    TreeNode* root = nullptr;
    root = LoadTreeFromFile();

    while (ProcessOfAuthorization(currentUser))
    {
        if (currentUser.role == "admin")
        {
            AdminModule(root);
        }
        else
        {
            UserModule(root);
        }
    }

    return 0;
}