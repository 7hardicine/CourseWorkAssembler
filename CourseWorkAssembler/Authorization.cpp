#include "Authorization.h"
#include "AsmLib.h"
#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;

// Ключ шифра
const char* KEY = "erg";

// Вспомогательная функция для шифрования строки (через ASM)
string EncryptPass(string pass) {
    char* buf = new char[pass.length() + 1];
    strcpy_s(buf, pass.length() + 1, pass.c_str());
    AsmVigenereCipher(buf, KEY, true); // true = encrypt
    string res = buf;
    delete[] buf;
    return res;
}

bool ProcessOfAuthorization(UserAndAdmin& man) {
    bool flag = true;
    const char* fileName = "AllPeople.txt";
    while (flag) {
        system("cls");
        cout << "1. Войти\n2. Регистрация\n3. Выход\n";
        int choice = InputInt(">> ", 1, 3);
        if (choice == 3) return false;

        fstream file;
        // Проверка/создание файла
        file.open(fileName, ios::app); file.close();

        file.open(fileName, ios::in | ios::out | ios::app);
        if (!file.is_open()) {
            cout << "Ошибка файла.\n"; continue;
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

    // Шифруем введенный пароль для сверки
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
    string line, fLog, fPass, fRole;

    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t p1 = line.find(';');
        size_t p2 = line.find(';', p1 + 1);
        if (p1 == string::npos || p2 == string::npos) continue;

        fLog = line.substr(0, p1);
        fPass = line.substr(p1 + 1, p2 - p1 - 1);
        fRole = line.substr(p2 + 1);

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