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

bool ProcessOfAuthorization(UserAndAdmin&);
void Entrance(fstream&, UserAndAdmin&, bool*);
bool checkingFileForEntry(fstream&, UserAndAdmin&);
void Registration(fstream&, UserAndAdmin&, bool*);
bool checkingFileForReg(fstream&, UserAndAdmin&);

int GetUsersCount();                     
void PrintUsersArray(UserAndAdmin* arr, int count); 
string EncryptPass(string pass);         

void InputPassword(string& password);
