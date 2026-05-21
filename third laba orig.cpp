#include <iostream>
using namespace std;
#include <cstring>
#include <cctype>

/*
void makeQueue(Queue* queue) {
    queue->head = nullptr;
    queue->tail = nullptr;
    queue->size = 0;
}

void dobavlenieQueue(Queue* queue, int value) {
    NodeQueue* n = new NodeQueue;
    n->data = value;
    n->next = nullptr;

    if (queue->tail == nullptr) {
        queue->head = n;
        queue->tail = n;
    }
    else {
        queue->tail->next = n;
        queue->tail = n;
    }
    queue->size++;
}

int deleteQueue(Queue* queue) {
    if (queue->head == nullptr) return 0;

    int value = queue->head->data;
    NodeQueue* temp = queue->head;
    queue->head = queue->head->next;

    if (queue->head == nullptr) {
        queue->tail = nullptr;
    }

    delete temp;
    queue->size--;
    return value;
}



bool isEmpty(Queue* queue) {
    return queue->head == nullptr;
}

int getSize(Queue* queue) {
    return queue->size;
}

void clearQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        deleteQueue(queue);
    }
}
*/

//стек

struct Node {
    int data;
    Node* next;
};

struct Stack {
    Node* top;
};

void push(Stack* s, int value) {
    Node* n = new Node;
    n->data = value;
    n->next = s->top;
    s->top = n;
}

int pop(Stack* stack) {
    if (!stack->top) return 0;
    int value = stack->top->data;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    delete temp;
    return value;
}

bool isEmpty(Stack* stack) {
    return stack->top == nullptr;
}


int letters[256];
bool lettersUsed[256];

void setLetter(char name, int value) {
    letters[(int)name] = value;
    lettersUsed[(int)name] = true;
}

int getLetter(char name) {
    return letters[(int)name];
}

bool isOperation(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}


void collectLetters(const char* vyragenie, char* letterList, int& letterCount) {
    letterCount = 0;
    for (int i = 0; vyragenie[i]; i++) {
        char c = vyragenie[i];
        if (isalpha(c)) {
            bool flag = false;
            for (int j = 0; j < letterCount; j++) {
                if (letterList[j] == c) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                letterList[letterCount++] = c;
            }
        }
    }
}


void convertation(const char* text, char* answer) {
    Stack operations;
    operations.top = nullptr;
    int j = 0;

    for (int i = 0; text[i]; i++) {
        char c = text[i];
        if (c == ' ') continue;

        if (isdigit(c)) {
            
            while (isdigit(text[i])) {
                answer[j++] = text[i++];
            }
            answer[j++] = ' ';
            i--;
        }
        else if (isalpha(c)) {
            answer[j++] = c;
            answer[j++] = ' ';
        }
        else if (c == '(') {
            push(&operations, '(');
        }
        else if (c == ')') {
            while (!isEmpty(&operations) && operations.top->data != '(') {
                answer[j++] = pop(&operations);
                answer[j++] = ' ';
            }
            pop(&operations);
        }
        else if (isOperation(c)) {
            while (!isEmpty(&operations) && operations.top->data != '(' && priority(operations.top->data) >= priority(c)) {
                answer[j++] = pop(&operations);
                answer[j++] = ' ';
            }
            push(&operations, c);
        }
    }

    while (!isEmpty(&operations)) {
        answer[j++] = pop(&operations);
        answer[j++] = ' ';
    }
    answer[j] = '\0';
}


int vychislenie(const char* vyragenie) {
    Stack stack;
    stack.top = nullptr;

    for (int i = 0; vyragenie[i]; i++) {
        char c = vyragenie[i];
        if (c == ' ') continue;
          
        if (isdigit(c)) {

            int num = 0;
            while (isdigit(vyragenie[i])) {
                num = num * 10 + (vyragenie[i] - '0');
                i++;
            }
            push(&stack, num);
            i--;
        }
        else if (isalpha(c)) {
            if (!lettersUsed[(int)c]) {
                cout << "Ошибка: переменная " << c << " не инициализирована!" << endl;
                return 0;
            }
            push(&stack, getLetter(c));
        }
        else if (isOperation(c)) {
            int numTwo = pop(&stack);
            int numOne = pop(&stack);
            int result = 0;
            if (c == '+') result = numOne + numTwo;
            else if (c == '-') result = numOne - numTwo;
            else if (c == '*') result = numOne * numTwo;
            else if (c == '/') result = numOne / numTwo;
            push(&stack, result);
        }
    }
    return pop(&stack);
}


int vychisleniePolsk(const char* vyragenie) {
    Stack stack;
    stack.top = nullptr;
    int len = strlen(vyragenie);

    for (int i = len - 1; i >= 0; i--) {
        char c = vyragenie[i];
        if (c == ' ') continue;

        if (isdigit(c)) {
            int num = 0;
            int stepen = 1;
            while (i >= 0 && isdigit(vyragenie[i])) {
                num = num + (vyragenie[i] - '0') * stepen;
                stepen *= 10;
                i--;
            }
            push(&stack, num);
            i++;
        }
        else if (isalpha(c)) {
            if (!lettersUsed[(int)c]) {
                cout << "Ошибка: переменная " << c << " не инициализирована!" << endl;
                return 0;
            }
            push(&stack, getLetter(c));
        }
        else if (isOperation(c)) {
            int numOne = pop(&stack);
            int numTwo = pop(&stack);
            int result = 0;
            if (c == '+') result = numOne + numTwo;
            else if (c == '-') result = numOne - numTwo;
            else if (c == '*') result = numOne * numTwo;
            else if (c == '/') result = numOne / numTwo;
            push(&stack, result);
        }
    }
    return pop(&stack);
}

//очередь

struct NodeQueue {
    char data[20];
    NodeQueue* next;
};

struct Queue {
    NodeQueue* head;
    NodeQueue* tail;
    int size;
};

void klaviatura(Queue* queue) {
    NodeQueue* newQ = new NodeQueue;
    char dat[20];
    NodeQueue* temp = queue->head->next;
    for (int i(0); i < 20; i++) {
        cin >> dat[i];
        newQ->data[i] = dat[i];
    }
    
    newQ->next = nullptr;
    queue-> tail->next = newQ;
    queue->tail = newQ;
    delete queue->head;
    queue->head = temp;

}

void vyvod(Queue* queue) {
    for (int i(0); i < 20; i++) {
        cout << queue->head->data[i];
    }
}




int main() {
    setlocale(LC_ALL, "Russian");
    char vyragenie[100];
    int choice;

    while (true) {
        for (int i = 0; i < 256; i++) {
            lettersUsed[i] = false;
        }

        cout << "\n1. Стандартный счёт\n";
        cout << "2. Обратная Польская нотация\n";
        cout << "3. Прямая Польская нотация\n";
        cout << "Выбор: ";
        cin >> choice;
        cin.ignore();
        if (choice == 0) {
            return 0;
        }

        cout << "Введите выражение: ";
        cin.getline(vyragenie, 100);

        char lettersList[100];
        int lettersCount = 0;
        collectLetters(vyragenie, lettersList, lettersCount);

        if (lettersCount > 0) {
            cout << "\nОбнаружены переменные: ";
            for (int i = 0; i < lettersCount; i++) {
                cout << lettersList[i] << " ";
            }
            cout << endl;

            cout << "Введите их значения: ";
            char name;
            int value;
            for (int i = 0; i < lettersCount; i++) {
                cin >> name;
                cin.get();
                cin >> value;
                setLetter(name, value);
            }
            cin.get();
            cout << endl;
        }
        else {
            cout << "Переменные не обнаружены.\n";
        }

        int result = 0;
        if (choice == 1) {
            char answer[200];
            convertation(vyragenie, answer);
            cout << "Нотация: " << answer << endl;
            result = vychislenie(answer);
        }
        else if (choice == 2) {
            result = vychislenie(vyragenie);
        }
        else if (choice == 3) {
            result = vychisleniePolsk(vyragenie);
        }


        cout << "Результат: " << result << endl;
        
    }

    return 0;
}