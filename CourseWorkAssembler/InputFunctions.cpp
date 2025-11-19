#include "InputFunctions.h"
int InputInt(const char* query, int minValue, int maxValue)
{
	cout << query;
	int choice;
	cin >> choice;
	while (cin.fail() || choice<minValue || choice> maxValue)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Ошибка ввода. Повторите попытку:";
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
	while (cin.fail() || choice<minValue)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Ошибка ввода. Повторите попытку:";
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
