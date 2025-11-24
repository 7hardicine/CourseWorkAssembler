#include "TreeUtils.h"
#include "AsmLib.h"
#include "InputFunctions.h"
#include <iostream>
#include <iomanip>

using namespace std;

void PrintHeader() {
    cout << left << setw(6) << "No" << setw(15) << "Dest" << setw(10) << "Date"
        << setw(8) << "Dep" << setw(8) << "Arr" << setw(10) << "Price"
        << setw(8) << "Left" << setw(8) << "Sold" << endl;
}

void PrintTrain(const Train& t) {
    cout << left << setw(6) << t.number
        << setw(15) << t.destination
        << setw(10) << t.depDate
        << t.depH << ":" << setfill('0') << setw(2) << t.depM << setfill(' ') << "  "
        << t.arrH << ":" << setfill('0') << setw(2) << t.arrM << setfill(' ') << "  "
        << setw(10) << t.price
        << setw(8) << t.ticketsLeft
        << setw(8) << t.ticketsSold << endl;
}

void AddNode(TreeNode*& root, Train data) {
    if (!root) {
        root = new TreeNode(data);
    }
    else {
        if (data.number < root->data.number)
            AddNode(root->left, data);
        else
            AddNode(root->right, data);
    }
}

void PrintTree(TreeNode* root) {
    if (!root) return;
    PrintTrain(root->data);
    PrintTree(root->left);
    PrintTree(root->right);
}

// Удаление узла
TreeNode* FindMin(TreeNode* root) {
    while (root->left != nullptr) root = root->left;
    return root;
}

TreeNode* DeleteNode(TreeNode* root, int num) {
    if (root == nullptr) return root;

    if (num < root->data.number) {
        root->left = DeleteNode(root->left, num);
    }
    else if (num > root->data.number) {
        root->right = DeleteNode(root->right, num);
    }
    else {
        // Узел найден
        // 1. Нет детей
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        // 2. Один ребенок
        else if (root->left == nullptr) {
            TreeNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root;
            root = root->left;
            delete temp;
        }
        // 3. Два ребенка
        else {
            TreeNode* temp = FindMin(root->right);
            root->data = temp->data; // Копируем данные
            root->right = DeleteNode(root->right, temp->data.number); // Удаляем дубликат
        }
    }
    return root;
}

void EditTrainData(TreeNode* node) {
    if (!node) return;
    cout << "Редактирование поезда #" << node->data.number << endl;
    cout << "Введите новые данные:\n";
    node->data.destination = InputStr("Пункт: ");
    node->data.depDate = InputStr("Дата: ");
    cout << "Время отпр (Ч М): "; cin >> node->data.depH >> node->data.depM;
    cout << "Время приб (Ч М): "; cin >> node->data.arrH >> node->data.arrM;
    cout << "Цена: "; cin >> node->data.price;
    node->data.ticketsLeft = InputInt("Остаток: ", 0);
    cin.ignore(256, '\n');
    cout << "Обновлено.\n";
}

void SearchBySoldRange(TreeNode* root, int minVal, int maxVal) {
    if (!root) return;
    if (root->data.ticketsSold >= minVal && root->data.ticketsSold <= maxVal) {
        PrintTrain(root->data);
    }
    SearchBySoldRange(root->left, minVal, maxVal);
    SearchBySoldRange(root->right, minVal, maxVal);
}

int CountNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}

void TreeToArray(TreeNode* root, Train* arr, int& index) {
    if (!root) return;
    arr[index++] = root->data;
    TreeToArray(root->left, arr, index);
    TreeToArray(root->right, arr, index);
}

void SortAndPrint(TreeNode* root) {
    int count = CountNodes(root);
    if (count == 0) {
        cout << "Список пуст." << endl;
        return;
    }

    Train* arr = new Train[count];
    int idx = 0;
    TreeToArray(root, arr, idx);

    // Сортировка вставками
    for (int i = 1; i < count; i++) {
        Train key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            bool needSwap = false;
            if (arr[j].destination > key.destination) needSwap = true;
            else if (arr[j].destination == key.destination) {
                if (arr[j].number > key.number) needSwap = true;
            }

            if (needSwap) {
                arr[j + 1] = arr[j];
                j--;
            }
            else break;
        }
        arr[j + 1] = key;
    }

    PrintHeader();
    for (int i = 0; i < count; i++) {
        PrintTrain(arr[i]);
    }
    delete[] arr;
}

TreeNode* FindByNumber(TreeNode* root, int num) {
    if (!root) return nullptr;
    if (root->data.number == num) return root;
    if (num < root->data.number) return FindByNumber(root->left, num);
    return FindByNumber(root->right, num);
}

void BuyTicketTask(TreeNode* root) {
    int num = InputInt("Номер поезда: ", 1);
    TreeNode* node = FindByNumber(root, num);
    if (!node) {
        cout << "Поезд не найден." << endl;
        return;
    }
    cout << "Билетов: " << node->data.ticketsLeft << endl;
    int count = InputInt("Купить: ", 1);
    int res = AsmBuyTicket(&node->data.ticketsLeft, &node->data.ticketsSold, count);
    if (res) cout << "Куплено! Осталось: " << node->data.ticketsLeft << endl;
    else cout << "Ошибка: мало билетов." << endl;
}

void TraverseFilter(TreeNode* root, const string& city, int minH, int maxH) {
    if (!root) return;
    if (AsmCheckFilter(root->data.destination.c_str(), city.c_str(), root->data.arrH, root->data.arrM, minH, maxH)) {
        cout << "Поезд #" << root->data.number
            << " Прибытие: " << root->data.arrH << ":" << root->data.arrM
            << " Билетов: " << root->data.ticketsLeft << endl;
    }
    TraverseFilter(root->left, city, minH, maxH);
    TraverseFilter(root->right, city, minH, maxH);
}

void FilterTrainsTask(TreeNode* root) {
    string city = InputStr("Город (x): ");
    int a = InputInt("С (час a): ", 0, 23);
    int b = InputInt("По (час b): ", a, 23);
    cout << "Поиск..." << endl;
    TraverseFilter(root, city, a, b);
}