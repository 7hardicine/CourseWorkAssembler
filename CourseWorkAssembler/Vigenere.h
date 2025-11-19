#pragma once

extern "C" {

	void ExtractKey(const char* fio, char* outKey);
	void VigenereEncrypt(char* text, const char* key);
	void VigenereDecrypt(char* text, const char* key);

}