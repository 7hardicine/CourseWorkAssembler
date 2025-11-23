#pragma once

extern "C" 
{
    void AsmVigenereCipher(char* text, const char* key, bool encrypt);
    int AsmBuyTicket(int* ticketsLeft, int* ticketsSold, int count);
    int AsmCheckFilter(const char* city, const char* targetCity, int arrH, int arrM, int minH, int maxH);
}