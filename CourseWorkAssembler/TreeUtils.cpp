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

// Прямой обход (Top-down)
void PrintTree(TreeNode* root) {
    if (!root) return;
    PrintTrain(root->data);
    PrintTree(root->left);
    PrintTree(root->right);
}

void SearchBySoldRange(TreeNode* root, int minVal, int maxVal) {
    if (!root) return;
    if (root->data.ticketsSold >= minVal && root->data.ticketsSold <= maxVal) {
        PrintTrain(root->data);
    }
    SearchBySoldRange(root->left, minVal, maxVal);
    SearchBySoldRange(root->right, minVal, maxVal);
}

// --- Сортировка без векторов ---

// 1. Считаем узлы
int CountNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}

// 2. Переносим данные в массив
void TreeToArray(TreeNode* root, Train* arr, int& index) {
    if (!root) return;
    arr[index++] = root->data; // Прямой порядок, но для сортировки неважно
    TreeToArray(root->left, arr, index);
    TreeToArray(root->right, arr, index);
}

// 3. Сортировка вставками и вывод
void SortAndPrint(TreeNode* root) {
    int count = CountNodes(root);
    if (count == 0) {
        cout << "Список пуст." << endl;
        return;
    }

    // Динамический массив
    Train* arr = new Train[count];
    int idx = 0;
    TreeToArray(root, arr, idx);

    // Сортировка вставками
    // Ключи: Пункт назначения (возр), затем Номер поезда (возр)
    for (int i = 1; i < count; i++) {
        Train key = arr[i];
        int j = i - 1;

        // Условие: пока пред. элемент "больше" текущего
        // Сравнение строк destination
        while (j >= 0) {
            bool needSwap = false;
            if (arr[j].destination > key.destination) {
                needSwap = true;
            }
            else if (arr[j].destination == key.destination) {
                if (arr[j].number > key.number) {
                    needSwap = true;
                }
            }

            if (needSwap) {
                arr[j + 1] = arr[j];
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
    }

    PrintHeader();
    for (int i = 0; i < count; i++) {
        PrintTrain(arr[i]);
    }

    delete[] arr; // Очистка памяти
}

// --- Индивидуальные задания ---

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

    // Вызов ASM
    int res = AsmBuyTicket(&node->data.ticketsLeft, &node->data.ticketsSold, count);

    if (res) cout << "Куплено! Осталось: " << node->data.ticketsLeft << endl;
    else cout << "Ошибка: мало билетов." << endl;
}

void TraverseFilter(TreeNode* root, const string& city, int minH, int maxH) {
    if (!root) return;

    // Вызов ASM для проверки
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