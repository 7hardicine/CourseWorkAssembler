#include "Authorization.h"
#include "AsmLib.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const char* KEY = "erg";
const char* FILE_NAME = "AllPeople.txt";

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
    cout << "--- ВХОД ---" << endl;
    man.login = InputStr("Логин: ");
    string rawPass = InputStr("Пароль: ");
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

void Registration(fstream& file, UserAndAdmin& man, bool* flag) {
    cout << "--- РЕГИСТРАЦИЯ ---" << endl;
    man.login = InputStr("Логин: ");

    if (checkingFileForReg(file, man)) {
        cout << "Логин занят.\n"; Sleep(1500); return;
    }

    string rawPass = InputStr("Пароль (лат): ");
    man.password = EncryptPass(rawPass);

    int r = InputInt("1-User, 2-Admin: ", 1, 2);
    man.role = (r == 2) ? "admin" : "user";

    // Запись в конец файла
    file.clear();
    file << endl << man.login << ";" << man.password << ";" << man.role;
    cout << "OK.\n"; Sleep(1000);
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

void SaveArrayToFile(UserAndAdmin* arr, int count) {
    ofstream file(FILE_NAME); // Перезапись файла
    for (int i = 0; i < count; i++) {
        file << arr[i].login << ";" << arr[i].password << ";" << arr[i].role;
        if (i < count - 1) file << endl;
    }
    file.close();
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