#include "Authorization.h"
#include "AsmLib.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include "FileProcessing.h"

using namespace std;

const char* KEY = "erg";

string EncryptPass(string pass) {
    if (pass.empty()) return "";
    char* buf = new char[pass.length() + 1];
    strcpy_s(buf, pass.length() + 1, pass.c_str());
    AsmVigenereCipher(buf, KEY, true);
    string res = buf;
    delete[] buf;
    return res;
}

bool ProcessOfAuthorization(UserAndAdmin& man) {
    bool flag = true;
    while (flag) {
        system("cls");
        cout << "1. Войти\n2. Регистрация\n3. Выход\n";
        int choice = InputInt(">> ", 1, 3);
        if (choice == 3) return false;

        fstream file;
        
        file.open(FILE_NAME, ios::app); file.close();

        file.open(FILE_NAME, ios::in | ios::out | ios::app);
        if (!file.is_open()) {
            cout << "Ошибка открытия файла.\n"; continue;
        }

        if (choice == 1) Entrance(file, man, &flag);
        else Registration(file, man, &flag);

        file.close();
    }
    return true;
}

void Entrance(fstream& file, UserAndAdmin& man, bool* flag) {
    cout << "ВХОД" << endl;
    man.login = InputStr("Логин: ");
    string rawPass;
    cout << "Пароль: ";
    InputPassword(rawPass);
    cout << std::endl;
    man.password = EncryptPass(rawPass);

    if (checkingFileForEntry(file, man)) {
        cout << "Успешно! Роль: " << man.role << endl;
        *flag = false;
        Sleep(1000);
    }
    else {
        cout << "Неверно.\n";
        Sleep(1500);
    }
}

void Registration(fstream& file, UserAndAdmin& man, bool* flag) {
    cout << "РЕГИСТРАЦИЯ" << endl;
    man.login = InputStr("Логин: ");

    if (checkingFileForReg(file, man)) {
        cout << "Логин занят.\n"; Sleep(1500); return;
    }

    string rawPass;
    cout << "Пароль (лат): ";
    InputPassword(rawPass);
    man.password = EncryptPass(rawPass);

    int r = InputInt("1-User, 2-Admin: ", 1, 2);
    man.role = (r == 2) ? "admin" : "user";

    file.clear();
    file << endl << man.login << ";" << man.password << ";" << man.role;
    cout << "OK.\n"; Sleep(1000);
}

bool checkingFileForEntry(fstream& file, UserAndAdmin& man) {
    file.clear();
    file.seekg(0);
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t p1 = line.find(';');
        size_t p2 = line.find(';', p1 + 1);
        if (p1 == string::npos || p2 == string::npos) continue;

        string fLog = line.substr(0, p1);
        string fPass = line.substr(p1 + 1, p2 - p1 - 1);
        string fRole = line.substr(p2 + 1);

        if (fLog == man.login && fPass == man.password) {
            man.role = fRole;
            return true;
        }
    }
    return false;
}

bool checkingFileForReg(fstream& file, UserAndAdmin& man) {
    file.clear();
    file.seekg(0);
    string line;
    while (getline(file, line)) {
        size_t p = line.find(';');
        if (p != string::npos) {
            string fLog = line.substr(0, p);
            if (fLog == man.login) return true;
        }
    }
    return false;
}

int GetUsersCount() {
    ifstream file(FILE_NAME);
    int count = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.find(';') != string::npos) {
            count++;
        }
    }
    file.close();
    return count;
}

void PrintUsersArray(UserAndAdmin* arr, int count) {
    if (!arr || count == 0) {
        cout << "Список пуст.\n";
        return;
    }
    cout << left << setw(5) << "No" << setw(20) << "Login" << setw(10) << "Role" << endl;
    cout << "------------------------------------" << endl;
    for (int i = 0; i < count; i++) {
        cout << left << setw(5) << i + 1
            << setw(20) << arr[i].login
            << setw(10) << arr[i].role << endl;
    }
}

void InputPassword(string& password)
{
    char ch;
    while (true) {
        ch = _getch();

        if (ch == 13) {
            break;
        }
        else if (ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            if (static_cast<unsigned char>(ch) > 127) {
                cout << "\nОшибка! Кириллица запрещена. Введите пароль заново: ";
                password.clear();
            }
            else {
                password += ch;
                cout << '*';
            }
        }
    }
}