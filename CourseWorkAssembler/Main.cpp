#include "Authorization.h"
#include "Menus.h"
#include "TreeUtils.h"
#include <iostream>
#include <windows.h> 

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    UserAndAdmin currentUser;

    if (ProcessOfAuthorization(currentUser)) 
    {

        TreeNode* root = nullptr;

        Train t1 = { 101, "Moscow", "25.11", 10, 0, 14, 30, 1500.0, 50, 10 };
        Train t2 = { 205, "Kazan",  "25.11", 12, 15, 20, 0,  2000.0, 10, 100 };
        Train t3 = { 102, "Moscow", "26.11", 21, 0,  11, 0,  1200.0, 100, 5 };

        AddNode(root, t1);
        AddNode(root, t2);
        AddNode(root, t3);

        if (currentUser.role == "admin") {
            AdminModule(root);
        }
        else {
            UserModule(root);
        }
    }

    return 0;
}