#include "Authorization.h" // Для UserAndAdmin struct
#include "TreeUtils.h"
#include "InputFunctions.h"
#include <iostream>

void AdminModule(TreeNode*& root) {
    while (true) {
        system("cls");
        cout << "[ADMIN] 1. Просмотр  2. Добавить  3. Покупка (ASM)  4. Фильтр (ASM)  5. Сорт  0. Выход\n";
        int c = InputInt(">> ", 0, 5);
        if (c == 0) break;

        switch (c) {
        case 1: PrintHeader(); PrintTree(root); system("pause"); break;
        case 2: {
            Train t;
            t.number = InputInt("Номер: ", 1);
            t.destination = InputStr("Пункт: ");
            t.depDate = InputStr("Дата: ");
            cout << "Время отпр (Ч М): "; cin >> t.depH >> t.depM;
            cout << "Время приб (Ч М): "; cin >> t.arrH >> t.arrM;
            cout << "Цена: "; cin >> t.price;
            t.ticketsLeft = InputInt("Остаток: ", 0);
            t.ticketsSold = InputInt("Продано: ", 0);
            cin.ignore(256, '\n');
            AddNode(root, t);
            break;
        }
        case 3: BuyTicketTask(root); system("pause"); break;
        case 4: FilterTrainsTask(root); system("pause"); break;
        case 5: SortAndPrint(root); system("pause"); break;
        }
    }
}

void UserModule(TreeNode*& root) {
    while (true) {
        system("cls");
        cout << "[USER] 1. Просмотр  2. Покупка (ASM)  3. Фильтр (ASM)  4. Поиск (билеты)  5. Сорт  0. Выход\n";
        int c = InputInt(">> ", 0, 5);
        if (c == 0) break;

        switch (c) {
        case 1: PrintHeader(); PrintTree(root); break;
        case 2: BuyTicketTask(root); break;
        case 3: FilterTrainsTask(root); break;
        case 4: {
            int minV = InputInt("Min: ", 0);
            int maxV = InputInt("Max: ", minV);
            PrintHeader();
            SearchBySoldRange(root, minV, maxV);
            break;
        }
        case 5: SortAndPrint(root); break;
        }
        system("pause");
    }
}