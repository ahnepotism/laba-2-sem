
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;
using namespace std::chrono;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
};

int getMax(int a, int b) {
    if (a > b) return a;
    else return b;
}

int height(Node* n) {
    if (n != nullptr) {
        return n->height;
    }
    else {
        return 0;
    }
}


int getBalance(Node* n) {
    if (n != nullptr) {
        int leftHeight = height(n->left);
        int rightHeight = height(n->right);
        return leftHeight - rightHeight;
    }
    else {
        return 0;
    }
}


Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;
    x->right = y;
    y->left = temp;
    y->height = getMax(height(y->left), height(y->right)) + 1;
    x->height = getMax(height(x->left), height(x->right)) + 1;
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;
    y->left = x;
    x->right = temp;
    x->height = getMax(height(x->left), height(x->right)) + 1;
    y->height = getMax(height(y->left), height(y->right)) + 1;
    return y;
}

Node* insert(Node* node, int key) {
    if (node == nullptr) {
        Node* newNode = new Node(); 
        newNode->key = key;
        newNode->height = 1;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    else {
        return node;
    }

    node->height = 1 + getMax(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left) current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) { temp = root; root = nullptr; }
            else *root = *temp;
            delete temp;
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (!root) return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

bool search(Node* root, int key) {
    if (!root) return false;
    if (root->key == key) return true;
    return key < root->key ? search(root->left, key) : search(root->right, key);
}

void collectKeys(Node* root, ofstream& file) {
    if (!root) return;
    file << root->key << " ";
    collectKeys(root->left, file);
    collectKeys(root->right, file);
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}


void printTree(Node* root, const char* otstup = "", bool isRight = false, bool isRoot = true) {
    if (!root) return;

    if (root->right) {
        char otstupRight[256];
        int i = 0;
        while (otstup[i] != '\0' && i < 240) {
            otstupRight[i] = otstup[i];
            i++;
        }
        const char* append = (isRight || isRoot) ? "      " : "|     ";
        int j = 0;
        while (append[j] != '\0') {
            otstupRight[i++] = append[j++];
        }
        otstupRight[i] = '\0';

        printTree(root->right, otstupRight, true, false);
    }

    cout << otstup;
    if (isRoot) cout << "--> ";
    else {
        cout << (isRight ? " . --" : " ` --") << "> ";
    }
    cout << root->key << endl;

    if (root->left) {
        char otstupLeft[256];
        int i = 0;
        while (otstup[i] != '\0' && i < 240) {
            otstupLeft[i] = otstup[i];
            i++;
        }
        const char* append = (!isRight || isRoot) ? "      " : "|     ";
        int j = 0;
        while (append[j] != '\0') {
            otstupLeft[i++] = append[j++];
        }
        otstupLeft[i] = '\0';

        printTree(root->left, otstupLeft, false, false);
    }
}

void printTreeToFile(Node* root, ofstream& file, const char* indent = "", bool isRight = false, bool isRoot = true) {
    if (!root) return;

    if (root->right) {
        char nextIndent[256];
        int i = 0;
        while (indent[i] != '\0' && i < 240) { nextIndent[i] = indent[i]; i++; }
        const char* append = (isRight || isRoot) ? "      " : "|     ";
        int j = 0;
        while (append[j] != '\0') { nextIndent[i++] = append[j++]; }
        nextIndent[i] = '\0';
        printTreeToFile(root->right, file, nextIndent, true, false);
    }

    file << indent;
    if (isRoot) {
        file << "--> ";
    }
    else {
        if (isRight) file << " . --> ";
        else file << " ` --> ";
    }
    file << root->key << "\n";

    if (root->left) {
        char nextIndent[256];
        int i = 0;
        while (indent[i] != '\0' && i < 240) { nextIndent[i] = indent[i]; i++; }
        const char* append = (!isRight || isRoot) ? "      " : "|     ";
        int j = 0;
        while (append[j] != '\0') { nextIndent[i++] = append[j++]; }
        nextIndent[i] = '\0';
        printTreeToFile(root->left, file, nextIndent, false, false);
    }
}

bool searching(Node* node, int key) {
    //if (!node) return false;
    if (node->key == key) return true;
    if (key < node->key) {
        search(node->left, key);
    }
    else {
        search(node->right, key);
    }
}

void diapozon(Node* root) {
    int numOne;
    int numTwo;
    bool flag = false;
    cout << "Введите диапозон чисел: ";
    cin >> numOne;
    cin >> numTwo;
    for (numOne; numOne <= numTwo; numOne++) {
        flag = searching(root, numOne);
        if (flag) {
            cout << numOne << "\n";
        }
        flag = false;
    } 

    
}

int main() {
    setlocale(LC_ALL, "Russian");
    Node* root = nullptr;
    int choice;

    while (true) {
        cout << "\n1. Формирование дерева (а - случайные, б - ввод)\n";
        cout << "2. Вывод дерева\n";
        cout << "3. Скорость вставки, удаления и поиска\n";
        cout << "4. Скорость проверки баланса\n";
        cout << "5. Генерация практических заданий по вариантам\n";
        cout << "0. Выход\nВыбор: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            char sub;
            cout << "Выберите (a/b): "; cin >> sub;
            auto start = high_resolution_clock::now();
            if (sub == 'a') {
                int n; cout << "N: "; cin >> n;
                mt19937 rng(time(0));
                uniform_int_distribution<int> dist(-99, 99);
                for (int i = 0; i < n; ++i) root = insert(root, dist(rng));
            }
            else {
                cout << "Введите числа (любая буква для конца): ";
                int val;
                while (cin >> val) root = insert(root, val);
                cin.clear(); cin.ignore(1000, '\n');
            }
            auto stop = high_resolution_clock::now();
            cout << "Время формирования: " << duration_cast<nanoseconds>(stop - start).count() << " нс\n";
            break;
        }
        case 2:
            if (!root) cout << "Дерево пусто\n";
            else printTree(root);
            break;

        case 3: {
            int subChoice;
            cout << "\nСКОРОСТЬ ОПЕРАЦИЙ\n";
            cout << "1. Замер скорости вставки\n";
            cout << "2. Замер скорости поиска\n";
            cout << "3. Замер скорости удаления\n";
            cout << "Выбор операции: ";
            cin >> subChoice;

            if (subChoice == 1) {
                int key;
                cout << "Введите число для вставки: ";
                cin >> key;

                auto start = high_resolution_clock::now();
                root = insert(root, key);
                auto stop = high_resolution_clock::now();

                cout << "Элемент " << key << " добавлен.\n";
                cout << "Время вставки: " << duration_cast<nanoseconds>(stop - start).count() << " нс\n";

            }
            else if (subChoice == 2) {
                int key;
                cout << "Введите число для поиска: ";
                cin >> key;

                auto start = high_resolution_clock::now();
                bool found = search(root, key);
                auto stop = high_resolution_clock::now();

                if (found) {
                    cout << "Элемент " << key << " найде в дереве.\n";
                }
                else {
                    cout << "Элемент " << key << " не найден в дереве.\n";
                }
                cout << "Время поиска: " << duration_cast<nanoseconds>(stop - start).count() << " нс\n";

            }
            else if (subChoice == 3) {
                int key;
                cout << "Введите число для удаления: ";
                cin >> key;

                if (!search(root, key)) {
                    cout << "Ошибка: Элемента " << key << " нет в дереве, удалять нечего.\n";
                }
                else {
                    auto start = high_resolution_clock::now();
                    root = deleteNode(root, key);
                    auto stop = high_resolution_clock::now();

                    cout << "Элемент " << key << " успешно удален.\n";
                    cout << "Время удаления: " << duration_cast<nanoseconds>(stop - start).count() << " нс\n";
                }
            }
            else {
                cout << "Неверный ввод.\n";
            }
            break;
        }
        case 4: {
            auto s = high_resolution_clock::now();
            int b = getBalance(root);
            auto e = high_resolution_clock::now();
            cout << "Проверка баланса: " << duration_cast<nanoseconds>(e - s).count() << " нс (Баланс корня: " << b << ")\n";
            break;
        }
        case 5: {
            int variantsCount;
            cout << "Введите количество вариантов для генерации: ";
            cin >> variantsCount;
            ofstream taskFile("output_task.txt");
            ofstream keyFile("output_key.txt");
            ofstream ansFile("output_ans.txt");

            if (!taskFile.is_open() || !keyFile.is_open() || !ansFile.is_open()) {
                cout << "Ошибка открытия файлов для записи!\n";
                break;
            }
            mt19937 rng(time(0));
            uniform_int_distribution<int> dist(-99, 99);

            for (int v = 1; v <= variantsCount; ++v) {
                int arr[7] = { 0 };
                for (int i = 0; i < 7; ++i) {
                    int num;
                    bool unique;
                    do {
                        num = dist(rng);
                        unique = true;
                        for (int j = 0; j < i; ++j) {
                            if (arr[j] == num) {
                                unique = false;
                                break;
                            }
                        }
                    } while (!unique);
                    arr[i] = num;
                }
                int insertKey;
                bool uniqueInsert;
                do {
                    insertKey = dist(rng);
                    uniqueInsert = true;
                    for (int i = 0; i < 7; ++i) {
                        if (arr[i] == insertKey) {
                            uniqueInsert = false;
                            break;
                        }
                    }
                } while (!uniqueInsert);
                int deleteKey = arr[3];
                taskFile << "ВАРИАНТ " << v << "\n";
                taskFile << "1. Постройте АВЛ-дерево из следующего массива чисел:\n   ";
                for (int i = 0; i < 7; ++i) {
                    taskFile << arr[i] << " ";
                }
                taskFile << "\n2. В полученное дерево последовательно вставьте элемент: " << insertKey << "\n";
                taskFile << "3. Из дерева, полученного после шага 2, удалите элемент: " << deleteKey << "\n\n";

                Node* taskRoot = nullptr;

                for (int i = 0; i < 7; ++i) {
                    taskRoot = insert(taskRoot, arr[i]);
                }
                ansFile << "ОТВЕТЫ К ВАРИАНТУ " << v << "\n";
                ansFile << "Шаг 1. АВЛ-дерево после создания из исходного массива:\n";
                printTreeToFile(taskRoot, ansFile);
                ansFile << "\n";

                taskRoot = insert(taskRoot, insertKey);
                ansFile << "Шаг 2. АВЛ-дерево после вставки элемента " << insertKey << ":\n";
                printTreeToFile(taskRoot, ansFile);
                ansFile << "\n";

                taskRoot = deleteNode(taskRoot, deleteKey);
                ansFile << "Шаг 3. АВЛ-дерево после удаления элемента " << deleteKey << ":\n";
                printTreeToFile(taskRoot, ansFile);
                ansFile << "\n\n";

                keyFile << "Вариант " << v << ": ";
                collectKeys(taskRoot, keyFile);
                keyFile << "\n";

                freeTree(taskRoot);
            }

            taskFile.close();
            keyFile.close();
            ansFile.close();

            cout << "Задания успешно сгенерированы в файлы!\n";
            break;
        }
        case 6: {
            int numOne;
            int numTwo;
            bool flag = false;
            cout << "Введите диапозон чисел: ";
            cin >> numOne;
            cin >> numTwo;
            for (numOne; numOne <= numTwo; numOne++) {
                flag = search(root, numOne);
                if (flag) {
                    cout << numOne << "\n";
                }
                flag = false;
            }
        }

        }


    }
    return 0;
}
