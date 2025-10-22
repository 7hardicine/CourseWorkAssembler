#include <iostream>
#include <string>
#include "Auth.h"

extern "C" void VigenereEncryptEnglish(const char* input, const char* key, char* output);

bool IsOnlyEnglish(const std::string& text)
{
    for (unsigned char c : text) {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ')) return false;
    }
    return true;
}

void Authorization()
{
    std::string username, password;
    bool isRunning = true;

    while (isRunning) {
        system("cls");
        std::cout << "~Авторизация в аккаунт~\n\n~-~-~-~-~-~-~-~-~-~-~-~\n\n";
        std::cout << "Введите имя пользователя: ";
        std::getline(std::cin, username);

        if (username.empty() || !IsOnlyEnglish(username))
        {
            std::cout << "Имя пользователя может содержать только английский алфавит и цифры !\n";
            std::cout << "Нажмите Enter, чтобы повторить ввод...";
            std::cin.get();
            continue;
        }

        std::cout << "Введите пароль: ";
        std::getline(std::cin, password);

        if (password.empty() || !IsOnlyEnglish(password))
        {
            std::cout << "Пароль может содержать только английский алфавит и цифры !\n";
            std::cout << "Нажмите Enter, чтобы повторить ввод...";
            std::cin.get();
            continue;
        }

        isRunning = false;
    }

    int choice;
    std::cout << "\nЗашифровать данные Виженером? (1 - Да, 0 - Нет): ";
    std::cin >> choice;
    std::cin.ignore();

    std::string outputUsername;
    std::string outputPassword;

    if (choice == 1) {
        std::cout << "\nВведите ключ: ";
        std::string key;
        std::getline(std::cin, key);

        outputUsername.resize(username.size() + 1);
        outputPassword.resize(password.size() + 1);

        VigenereEncryptEnglish(username.c_str(), key.c_str(), &outputUsername[0]);
        VigenereEncryptEnglish(password.c_str(), key.c_str(), &outputPassword[0]);

        outputUsername.resize(strlen(outputUsername.c_str()));
        outputPassword.resize(strlen(outputPassword.c_str()));

        std::cout << "\nИмя и пароль зашифрованы.\n";
    }
    else {
        outputUsername = username;
        outputPassword = password;
    }

    std::cout << "\n=== РЕЗУЛЬТАТ ===\n";
    std::cout << "Имя пользователя: " << outputUsername << "\n";
    std::cout << "Пароль: " << outputPassword << "\n";
    std::cout << "\nАвторизация завершена.\n";
}