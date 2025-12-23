#include "InputFunctions.h"
#include "FileProcessing.h"

int InputInt(const char* query, int minValue, int maxValue)
{
    cout << query;
    int choice;
    cin >> choice;
    while (cin.fail() || choice < minValue || choice > maxValue)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Ошибка ввода. Повторите попытку: ";
        cin >> choice;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

int InputInt(const char* query, int minValue)
{
    cout << query;
    int choice;
    cin >> choice;
    while (cin.fail() || choice < minValue)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Ошибка ввода. Повторите попытку: ";
        cin >> choice;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

string InputStr(const char* query)
{
    cout << query;
    string str = "";
    getline(cin, str);
    return str;
}

bool IsLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int GetDaysInMonth(int month, int year) {
    int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (IsLeap(year) && month == 2) return 29;
    return days[month];
}

bool IsValidDateString(string date) {
    if (date.length() != 10) return false;
    if (date[2] != '.' || date[5] != '.') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return false;
    }

    try {
        int d = stoi(date.substr(0, 2));
        int m = stoi(date.substr(3, 2));
        int y = stoi(date.substr(6, 4));

        if (y < 1900 || y > 2100) return false; 
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > GetDaysInMonth(m, y)) return false;

        return true;
    }
    catch (...) {
        return false;
    }
}

string InputDate(const char* query) {
    while (true) {
        string date = InputStr(query);
        if (IsValidDateString(date)) {
            return date;
        }
        cout << "Ошибка! Формат ДД.ММ.ГГГГ или некорректная дата (например 30.02).\n";
    }
}

void InputTime(const char* query, int& h, int& m) {
    while (true) {
        cout << query;
        if (cin >> h >> m) {
            if (h >= 0 && h <= 23 && m >= 0 && m <= 59) {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                return;
            }
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Ошибка! Часы (0-23) и минуты (0-59).\n";
    }
}