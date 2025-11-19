#include <iostream>
#include <clocale>
#include <Windows.h>
#include "Authorization.h"
#include "Vigenere.h"

using namespace std;

int main() 
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char* fio = "Tselkovikov Yury Evgenevich";
    char key[16];

    // Генерируем ключ "лиг"
    ExtractKey(fio, key);
    cout << "Сгенерированный ключ = " << key << endl;

    char text[256] = "Example";

    // Шифрование
    VigenereEncrypt(text, key);
    cout << "Зашифрованный текст = " << text << endl;

    // Расшифровка
    VigenereDecrypt(text, key);
    cout << "Расшифрованный текст = " << text << endl;

    return 0;
}
