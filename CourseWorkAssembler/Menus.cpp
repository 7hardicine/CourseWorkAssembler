#include "Authorization.h"
#include "TreeUtils.h"
#include "InputFunctions.h"
#include <iostream>
#include <fstream>

void AdminModule(TreeNode*& root) {
    while (true) {
        system("cls");
        cout << "=== МОДУЛЬ АДМИНИСТРАТОРА ===\n";
        cout << "1. Работа с учетными записями\n";
        cout << "2. Работа с данными\n";
        cout << "0. Выход\n";
        int c = InputInt(">> ", 0, 2);

        if (c == 0) break;
        switch (c) {
        case 1: AdminAccountsMenu(); break;
        case 2: AdminDataMenu(root); break;
        }
    }
}

void AdminAccountsMenu() {
    int count = 0;
    UserAndAdmin* users = nullptr;

    while (true) {
        // Каждый раз перезагружаем массив, чтобы иметь актуальные данные
        if (users) delete[] users;
        users = LoadUsersToArray(count);

        system("cls");
        cout << "--- Учетные записи ---\n";
        cout << "1. Просмотр\n";
        cout << "2. Добавление\n";
        cout << "3. Редактирование\n";
        cout << "4. Удаление\n";
        cout << "0. Назад\n";
        int c = InputInt(">> ", 0, 4);

        if (c == 0) break;
        switch (c) {
        case 1: // Просмотр
            PrintUsersArray(users, count);
            system("pause");
            break;
        case 2: // Добавление
        {
            // Для добавления просто дописываем в файл через режим ios::app
            UserAndAdmin newUser;
            newUser.login = InputStr("Новый логин: ");

            // Проверка уникальности
            bool exists = false;
            for (int i = 0; i < count; i++) {
                if (users[i].login == newUser.login) exists = true;
            }
            if (exists) {
                cout << "Логин занят!\n"; system("pause"); break;
            }

            string rp = InputStr("Пароль: ");
            newUser.password = EncryptPass(rp);
            int r = InputInt("Роль (1-user, 2-admin): ", 1, 2);
            newUser.role = (r == 2) ? "admin" : "user";

            ofstream f("AllPeople.txt", ios::app);
            f << endl << newUser.login << ";" << newUser.password << ";" << newUser.role;
            f.close();

            cout << "Добавлено.\n";
            system("pause");
            break;
        }
        case 3: // Редактирование
        {
            PrintUsersArray(users, count);
            if (count == 0) { system("pause"); break; }
            int idx = InputInt("Введите No для ред.: ", 1, count) - 1;

            cout << "Редактирование " << users[idx].login << endl;
            string np = InputStr("Новый пароль (Enter - оставить): ");
            if (!np.empty()) {
                users[idx].password = EncryptPass(np);
            }
            int r = InputInt("Новая роль (1-user, 2-admin): ", 1, 2);
            users[idx].role = (r == 2) ? "admin" : "user";

            // Сохраняем измененный массив
            SaveArrayToFile(users, count);
            cout << "Сохранено.\n";
            system("pause");
            break;
        }
        case 4: // Удаление
        {
            PrintUsersArray(users, count);
            if (count == 0) { system("pause"); break; }
            int idx = InputInt("Введите No для удаления: ", 1, count) - 1;

            if (users[idx].login == "admin") {
                cout << "Нельзя удалить главного админа!\n"; system("pause"); break;
            }

            // Создаем новый массив на 1 меньше
            UserAndAdmin* newArr = new UserAndAdmin[count - 1];
            int j = 0;
            for (int i = 0; i < count; i++) {
                if (i == idx) continue; // Пропускаем удаляемого
                newArr[j++] = users[i];
            }

            SaveArrayToFile(newArr, count - 1);
            delete[] newArr;

            cout << "Удалено.\n";
            system("pause");
            break;
        }
        }
    }
    if (users) delete[] users;
}

void AdminDataMenu(TreeNode*& root) {
    while (true) {
        system("cls");
        cout << "--- Работа с данными (Admin) ---\n";
        cout << "1. Режим редактирования\n";
        cout << "2. Режим обработки\n";
        cout << "0. Назад\n";
        int c = InputInt(">> ", 0, 2);

        if (c == 0) break;
        switch (c) {
        case 1: AdminEditMode(root); break;
        case 2: AdminProcessMode(root); break;
        }
    }
}

void AdminEditMode(TreeNode*& root) {
    while (true) {
        system("cls");
        cout << "[РЕДАКТИРОВАНИЕ] 1. Просмотр  2. Добавление  3. Редактирование  4. Удаление  0. Назад\n";
        int c = InputInt(">> ", 0, 4);
        if (c == 0) break;

        switch (c) {
        case 1: // Просмотр
            PrintHeader(); PrintTree(root); system("pause"); break;
        case 2: // Добавление
        {
            Train t;
            t.number = InputInt("Номер: ", 1);
            if (FindByNumber(root, t.number)) {
                cout << "Уже есть!\n"; system("pause"); break;
            }
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
        case 3: // Редактирование
        {
            int num = InputInt("Номер поезда: ", 1);
            TreeNode* node = FindByNumber(root, num);
            if (node) EditTrainData(node);
            else cout << "Не найдено.\n";
            system("pause");
            break;
        }
        case 4: // Удаление
        {
            int num = InputInt("Номер поезда: ", 1);
            root = DeleteNode(root, num);
            cout << "Удалено (если существовал).\n";
            system("pause");
            break;
        }
        }
    }
}

void AdminProcessMode(TreeNode* root) {
    while (true) {
        system("cls");
        cout << "[ОБРАБОТКА] 1. Инд. задание (Фильтр ASM)  2. Поиск  3. Сортировка  0. Назад\n";
        int c = InputInt(">> ", 0, 3);
        if (c == 0) break;

        switch (c) {
        case 1: FilterTrainsTask(root); system("pause"); break;
        case 2:
        {
            int num = InputInt("Номер поезда: ", 1);
            TreeNode* node = FindByNumber(root, num);
            if (node) { PrintHeader(); PrintTrain(node->data); }
            else cout << "Не найдено.\n";
            system("pause");
            break;
        }
        case 3: SortAndPrint(root); system("pause"); break;
        }
    }
}

void UserModule(TreeNode*& root) {
    
    UserDataMenu(root);
}

void UserDataMenu(TreeNode*& root) {
    while (true) {
        system("cls");
        cout << "=== МОДУЛЬ ПОЛЬЗОВАТЕЛЯ (Работа с данными) ===\n";
        cout << "1. Просмотр\n";
        cout << "2. Инд. задание (Покупка)\n";
        cout << "3. Поиск (по проданным)\n";
        cout << "4. Сортировка\n";
        cout << "0. Выход\n";
        int c = InputInt(">> ", 0, 4);

        if (c == 0) break;

        switch (c) {
        case 1: PrintHeader(); PrintTree(root); system("pause"); break;
        case 2: BuyTicketTask(root); system("pause"); break;
        case 3:
        {
            int minV = InputInt("Min проданных: ", 0);
            int maxV = InputInt("Max проданных: ", minV);
            PrintHeader();
            SearchBySoldRange(root, minV, maxV);
            system("pause");
            break;
        }
        case 4: SortAndPrint(root); system("pause"); break;
        }
    }
}