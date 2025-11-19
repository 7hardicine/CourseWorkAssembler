/*#include "Authorization.h"
#include <fstream>
#include <windows.h>
#include <iostream>
using namespace std;

bool ProcessOfAuthorization(UserAndAdmin& man)
{
    bool flag = true;
    const char* fileName = "AllPeople.txt";
    while (flag == true)
    {
        system("cls");
        cout << "\t***Меню авторизации и регистрации***" << endl;
        cout << "1—ВОЙТИ;" << endl;
        cout << "2—зарегистрироваться;" << endl;
        cout << "3—завершить работу программы;" << endl;
        int choice = InputInt("Выберите действие: ", 1, 3);
        system("cls");
        if (choice == 1 || choice == 2)
        {
            fstream file;
            file.open(fileName, ios::out | ios::in | ios::app);
            if (!file.is_open())
            {
                cout << "Ошибка: связь с файлом не установлена!\n";
                Sleep(5000);
            }
            else
            {
                if (choice == 1)
                    Entrance(file, man, &flag);
                else
                    Registration(file, man, &flag);
                file.close();
            }
        }
        else
        {
            cout << "До новых встреч!" << endl;
            return false;
        }
    }
    return true;
}
bool checkingFileForEntry(fstream& file, UserAndAdmin& man)
{
    int fileSize;
    file.seekg(0, ios::end);
    fileSize = file.tellg();
    file.seekg(0);
    if (fileSize != 0)
    {
        string str = "";
        while (!file.eof())
        {
            getline(file, str, ';');
            if (str[0] == '\n')
                str.erase(str.begin());
            if (str == man.login)
            {
                //encryptionAndDecryption(man.password);
                getline(file, str, ';');
                if (str == man.password)
                {
                    getline(file, man.role, ';');
                    return true;
                }
            }
        }
    }
}

*/