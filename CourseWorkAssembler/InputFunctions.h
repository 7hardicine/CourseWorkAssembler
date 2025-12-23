#pragma once
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int InputInt(const char* query, int minValue, int maxValue);
int InputInt(const char* query, int minValue);
string InputStr(const char* query);

// ÍÎÂÛÅ ÔÓÍÊÖÈÈ
string InputDate(const char* query);
void InputTime(const char* query, int& h, int& m);