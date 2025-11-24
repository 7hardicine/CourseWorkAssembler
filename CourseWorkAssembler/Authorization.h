#pragma once
#include "InputFunctions.h"
#include <string>
#include <fstream>

using namespace std;

struct UserAndAdmin
{
	string role;
	string login;
	string password;
};

// Основные функции авторизации
bool ProcessOfAuthorization(UserAndAdmin&);
void Entrance(fstream&, UserAndAdmin&, bool*);
bool checkingFileForEntry(fstream&, UserAndAdmin&);
void Registration(fstream&, UserAndAdmin&, bool*);
bool checkingFileForReg(fstream&, UserAndAdmin&);

// Новые функции для работы с массивом пользователей (без векторов)
int GetUsersCount();                      // Посчитать строки в файле
UserAndAdmin* LoadUsersToArray(int& count); // Загрузить в дин. массив
void SaveArrayToFile(UserAndAdmin* arr, int count); // Сохранить массив в файл
void PrintUsersArray(UserAndAdmin* arr, int count); // Вывод
string EncryptPass(string pass);          // Доступ к шифрованию из других модулей