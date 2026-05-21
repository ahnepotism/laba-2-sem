#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;
int const maxx = 99;
int const minn = 0;



struct List
{
	int data;
	List* head;
	List* tail;
};

List* createList(int length) {
    if (length <= 0) {
        cout << "Ошибка" << endl;
        return nullptr;
    }

    List* curr = nullptr;
    List* next = nullptr;

    for (int i = 0; i < length; i++) {
        List* spisok = new List;

        spisok->data = rand() % (maxx - minn + 1) + minn;
        spisok->head = nullptr;
        spisok->tail = nullptr;

        if (curr == nullptr) {
            curr = spisok;
            next = spisok;
        }
        else {
            next->tail = spisok;
            spisok->head = next;
            next = spisok;
        }
    }
    return curr;
}

List* createWhile() {
    int num = 0;
    List* curr = nullptr;
    List* next = nullptr;
    while (num != -1000) {
        cin >> num;
        if (num == -1000) break;
        List* spisok = new List;

        spisok->data = num;
        spisok->head = nullptr;
        spisok->tail = nullptr;

        if (curr == nullptr) {
            curr = spisok;
            next = spisok;
        }
        else {
            next->tail = spisok;
            spisok->head = next;
            next = spisok;
        }
    }
    return curr;
}


void vstavka(List* ourList) {
    cout << "Введите индекс элемента, после которого следует выполнить вставку: ";
    int numberOfVst;
    int znachenie;
    int counter(0);
    cin >> numberOfVst;
    cout << "\nВведите значение, которое примет вставка: ";
    cin >> znachenie;
    List* ourIndex = ourList;
    while (counter < numberOfVst && ourIndex!=nullptr) {
        ourIndex = ourIndex->tail;
        counter++;
    }
    List* vstavka = new List;
    vstavka->data = znachenie;
    vstavka->head = ourIndex;
    vstavka->tail = ourIndex->tail;
    
    if (ourIndex->tail != nullptr) {
        ourIndex->tail->head = vstavka;
    }

    ourIndex->tail = vstavka;

}

void deleting(List* ourList) {
    int choice;
    int numberOfVst;
    int znachenie;
    int counter(0);
    int indexOfDel;
    cout << "Как Вы хотите реализовать удаление элемента?:\n1 - по индексу\n2 - по значению\n";
    cin >> choice;
    if (choice == 1) {
        cout << "Введите индекс элемента, который следует удалить: ";
        cin >> numberOfVst;
        List* ourIndex = ourList;
        while (counter < numberOfVst && ourIndex != nullptr) {
            ourIndex = ourIndex->tail;
            counter++;
        }
        ourIndex->head->tail = ourIndex->tail;
        ourIndex->tail->head = ourIndex->head;
        delete ourIndex;
    }
    else {
        cout << "Введите значение элемента, который следует удалить: ";
        cin >> indexOfDel;
        List* ourIndex = ourList;
        while (ourIndex-> data!= indexOfDel && ourIndex != nullptr) {
            ourIndex = ourIndex->tail;
            counter++;
        }
        ourIndex->head->tail = ourIndex->tail;
        ourIndex->tail->head = ourIndex->head;
        delete ourIndex;
    }
}

void obmen(List* ourList) {
    int indexOne;
    int indexTwo;
    int counter = 0;
    int choice;
    int firstNum;
    int secNum;

    cout << "\n\nКак Вы хотите реализовать обмен элементов?:\n1 - по индексу\n2 - по значению\n";
    cin >> choice;
    if (choice == 1) {
        cout << "Введите первый индекс: ";
        cin >> indexOne;
        cout << "\nВведите второй индекс: ";
        cin >> indexTwo;
        List* ourIndexOne = ourList;
        List* ourIndexTwo = ourList;

        while (counter < indexOne && ourIndexOne != nullptr) {
            ourIndexOne = ourIndexOne->tail;
            counter++;
        }
        counter = 0;
        while (counter < indexTwo && ourIndexTwo != nullptr) {
            ourIndexTwo = ourIndexTwo->tail;
            counter++;
        }


        if (ourIndexOne->tail == ourIndexTwo) {

            List* OneHead = ourIndexOne->head;
            List* TwoTail = ourIndexTwo->tail;

            OneHead->tail = ourIndexTwo;
            TwoTail->head = ourIndexOne;
            ourIndexOne->head = ourIndexTwo;
            ourIndexOne->tail = TwoTail;
            ourIndexTwo->head = OneHead;
            ourIndexTwo->tail = ourIndexOne;

        }
        else {
            List* OneHead = ourIndexOne->head;
            List* OneTail = ourIndexOne->tail;
            List* TwoHead = ourIndexTwo->head;
            List* TwoTail = ourIndexTwo->tail;

            OneHead->tail = ourIndexTwo;
            OneTail->head = ourIndexTwo;

            TwoHead->tail = ourIndexOne;
            TwoTail->head = ourIndexOne;

            ourIndexOne->head = TwoHead;
            ourIndexOne->tail = TwoTail;

            ourIndexTwo->head = OneHead;
            ourIndexTwo->tail = OneTail;
        }
        
    }
    else {
        cout << "Введите значение первого элемента: ";
        cin >> firstNum;
        cout << "\nВведите значение второго элемента: ";
        cin >> secNum;
        List* ourIndexOne = ourList;
        List* ourIndexTwo = ourList;
        while (ourIndexOne->data != firstNum && ourIndexOne != nullptr) {
            ourIndexOne = ourIndexOne->tail;
            counter++;
        }
        counter = 0;
        while (ourIndexTwo->data != secNum && ourIndexTwo != nullptr) {
            ourIndexTwo = ourIndexTwo->tail;
            counter++;
        }

        if (ourIndexOne->tail == ourIndexTwo || ourIndexTwo->tail == ourIndexOne) {

            if (ourIndexOne->tail == ourIndexTwo) {
                List* OneHead = ourIndexOne->head;
                List* TwoTail = ourIndexTwo->tail;

                OneHead->tail = ourIndexTwo;
                TwoTail->head = ourIndexOne;
                ourIndexOne->head = ourIndexTwo;
                ourIndexOne->tail = TwoTail;
                ourIndexTwo->head = OneHead;
                ourIndexTwo->tail = ourIndexOne;
            }

            else {
                List* OneHead = ourIndexTwo->head;
                List* TwoTail = ourIndexOne->tail;

                OneHead->tail = ourIndexOne;
                TwoTail->head = ourIndexTwo;
                ourIndexTwo->head = ourIndexOne;
                ourIndexTwo->tail = TwoTail;
                ourIndexOne->head = OneHead;
                ourIndexOne->tail = ourIndexTwo;
            }

        }
        else {
            List* OneHead = ourIndexOne->head;
            List* OneTail = ourIndexOne->tail;
            List* TwoHead = ourIndexTwo->head;
            List* TwoTail = ourIndexTwo->tail;

            OneHead->tail = ourIndexTwo;
            OneTail->head = ourIndexTwo;

            TwoHead->tail = ourIndexOne;
            TwoTail->head = ourIndexOne;

            ourIndexOne->head = TwoHead;
            ourIndexOne->tail = TwoTail;

            ourIndexTwo->head = OneHead;
            ourIndexTwo->tail = OneTail;
        }


    }
}

void poluchenie(List* ourList) {
    int userIndex;
    int userChoice;
    int counter(0);
    int ourNum;
    int numIndex = 0;
    cout << "\n\nКак Вы хотите реализовать получение элемента?:\n1 - по индексу\n2 - по значению\n";
    cin >> userChoice;
    if (userChoice == 1) {
        cout << "\nВведите индекс: ";
        cin >> userIndex;
        List* ourIndexOne = ourList;

        while (counter < userIndex && ourIndexOne != nullptr) {
            ourIndexOne = ourIndexOne->tail;
            counter++;
        }
        if (ourIndexOne->head == nullptr) {
            cout << "Вы выбрали элемент под индексом: " << userIndex << "\nЕго значение = " << ourIndexOne->data << "\nЭто первый элемент, поэтому перед ним нет элементов" << ", а за ним идет элемент со значением " << ourIndexOne->tail->data << "\n";
        }
        else if (ourIndexOne->tail == nullptr) {
            cout << "Вы выбрали элемент под индексом: " << userIndex << "\nЕго значение = " << ourIndexOne->data << "\nПеред ним идет элемент со значением " << ourIndexOne->head->data << ". Это последний элемент, поэтому после него ничего не идет" << "\n";
        }
        else {
            cout << "Вы выбрали элемент под индексом: " << userIndex << "\nЕго значение = " << ourIndexOne->data << "\nПеред ним идет элемент со значением " << ourIndexOne->head->data << ", а за ним идет элемент со значением " << ourIndexOne->tail->data << "\n";
        }
        
    }
    else {
        cout << "Введите значение элемента: ";
        cin >> ourNum;
        List* ourIndexOne = ourList;
        while (ourIndexOne->data != ourNum && ourIndexOne != nullptr) {
            ourIndexOne = ourIndexOne->tail;
            counter++;
            numIndex++;
        }
        if (ourIndexOne->head == nullptr) {
            cout << "Вы выбрали элемент: " << ourIndexOne->data << "\nЕго индекс: " << numIndex << "\nЭто первый элемент, поэтому перед ним нет элементов" << ", а за ним идет элемент со значением " << ourIndexOne->tail->data << "\n";
        }
        else if (ourIndexOne->tail == nullptr) {
            cout << "Вы выбрали элемент: " << ourIndexOne->data << "\nЕго индекс: " << numIndex << "\nПеред ним идет элемент со значением " << ourIndexOne->head->data << ". Это последний элемент, поэтому после него ничего не идет" << "\n";
        }
        else {
            cout << "Вы выбрали элемент: " << ourIndexOne->data << "\nЕго индекс: " << numIndex << "\nПеред ним идет элемент со значением " << ourIndexOne->head->data << ", а за ним идет элемент со значением " << ourIndexOne->tail->data << "\n";
        }
    }
}

void printList(List* lis) {
	List* curr = lis;
	while (curr != nullptr) {
		cout << curr->data << " ";
		curr = curr->tail;
	}
	cout << endl;
}

void deleteList(List* lis) {
    while (lis != nullptr) {
        List* temp = lis;
        lis = lis->tail;
        delete temp;
    }
}

void deleteChet(List* ourList) {
    int counter = 0;
    while (ourList != nullptr) {
        List* del = ourList;
        if (counter % 2 != 0) {
            ourList = ourList->tail;
            del->head->tail = ourList;
            del->tail->head = ourList;
            delete del;
        }
        else {
            ourList = ourList->tail;
        }
        counter++;
    }
}

bool cycle(List* ourList) {
    int answer = 0;
    List* ptrOne = nullptr;
    List* ptrTwo = nullptr;
    while (true) {
        ptrOne = ptrOne->tail;
        ptrTwo = ptrTwo->tail->tail;
        if (ptrOne == ptrTwo) {
            answer = 1;
            break;
        }
    }
    return answer;
}

int* createMass(int lenght) {
    int* mass = new int[lenght];
    for (int i(0); i < lenght; i++) {
        mass[i] = rand() % (maxx - minn + 1) + minn;
    }
    return mass;
}

int* createWhileMass() {
    int num = 0;
    int counter = 0;
    int* mass = new int[1];
    while (num != -1000) {
        cin >> num;
        if (counter == 0) {
            mass[counter] = num;
            counter++;
        }
        else {
            int* newMass = new int[counter+1];
            for (int i(0); i < counter; i++) {
                newMass[i] = mass[i];
            }
            newMass[counter] = num;
            counter++;
            delete[] mass;
            mass = newMass;
        }
    }
    return mass;
}

void printMass(int* mass, int lenght) {

    for (int i(0); i < lenght; i++) {
        cout << mass[i] << ' ';
    }
}

void vstavkaMass(int*& mass, int lenght) {
    int ind;
    int znachenie;
    cout << "\nВведите индекс элемента, после которого следует выполнить вставку: ";
    cin >> ind;
    ind++;
    cout << "\nВведите значение элемента: ";
    cin >> znachenie;
    int newLenght = lenght + 1;
    int* newMass = new int[newLenght];
    for (int i(0); i < ind; i++) {

        newMass[i] = mass[i];
    }
    newMass[ind] = znachenie;
    for (int i = ind; i < lenght; i++) {
        newMass[i+1] = mass[i];
    }
    delete[] mass;
    mass = newMass;
}

void deleteMass(int*& mass, int lenght) {
    int choice;
    int numberOfVst;
    int znachenie;
    int counter(0);
    int indexOfDel;
    cout << "Как Вы хотите реализовать удаление элемента?:\n1 - по индексу\n2 - по значению\n";
    cin >> choice;
    if (choice == 1) {
        cout << "Введите индекс элемента, который следует удалить: ";
        cin >> indexOfDel;
        int newLenght = lenght - 1;
        int* newMass = new int[newLenght];
        for (int i(0); i < indexOfDel; i++) {
            newMass[i] = mass[i];
        }
        for (int i = indexOfDel +1; i < lenght; i++) {
            newMass[i - 1] = mass[i];
        }
        delete[] mass;
        mass = newMass;
    }
    else {
        cout << "Введите значение элемента, который следует удалить: ";
        cin >> indexOfDel;

        }
}

void obmenMass(int*& mass, int lenght) {
    int indexOne;
    int indexTwo;
    int counter = 0;
    int choice;
    int firstNum;
    int secNum;

    cout << "\n\nКак Вы хотите реализовать обмен элементов?:\n1 - по индексу\n2 - по значению\n";
    cin >> choice;
    if (choice == 1) {
        cout << "Введите первый индекс: ";
        cin >> indexOne;
        cout << "\nВведите второй индекс: ";
        cin >> indexTwo;
        int temp = mass[indexOne];
        mass[indexOne] = mass[indexTwo];
        mass[indexTwo] = temp;
    }
    else {
        cout << "Введите значение первого элемента: ";
        cin >> firstNum;
        cout << "\nВведите значение второго элемента: ";
        cin >> secNum;
        for (int i(0); i < lenght; i++) {
            if (mass[i] == firstNum || mass[i] == secNum) {
                if (mass[i] == firstNum) {
                    indexOne = i;
                }
                if (mass[i] == secNum) {
                    indexTwo = i;
                }
            }
        }
        int temp = mass[indexOne];
        mass[indexOne] = mass[indexTwo];
        mass[indexTwo] = temp;
    }
}

void poluchenieMass(int*& mass, int lenght) {
    int userIndex;
    int userChoice;
    int counter(0);
    int ourNum;
    int numIndex = 0;
    cout << "\n\nКак Вы хотите реализовать получение элемента?:\n1 - по индексу\n2 - по значению\n";
    cin >> userChoice;
    if (userChoice == 1) {
        cout << "\nВведите индекс: ";
        cin >> userIndex;
        if (userIndex == 0 || userIndex == lenght - 1) {
            if (userIndex == 0) {
                cout << "\nВы выбрали элемент под индексом " << userIndex << "\nЕго значение: " << mass[userIndex] << ". Это первый элемент, поэтому перед ним ничего нет, а за ним идет элемент со значением: " << mass[userIndex + 1];
            }
            else {
                cout << "\nВы выбрали элемент под индексом " << userIndex << "\nЕго значение: " << mass[userIndex] << ". Это последний элемент, поэтому после него ничего нет, а за перед идет элемент со значением: " << mass[userIndex - 1];
            }
        }
        else {
            cout << "\nВы выбрали элемент под индексом " << userIndex << "\nЕго значение: " << mass[userIndex] << ". Переред ним идет элемент со значением: " << mass[userIndex - 1] << ", а за ним идет элемент со значением : " << mass[userIndex + 1];
        }
    }
    else {
        cout << "Введите значение элемента: ";
        cin >> ourNum;
        for (int i(0); i < lenght; i++) {
            if (mass[i] == ourNum) {
                userIndex = i;
                break;
            }
        }
        if (userIndex == 0 || userIndex == lenght - 1) {
            if (userIndex == 0) {
                cout << "\nВы выбрали элемент под индексом " << userIndex << "\nЕго значение: " << mass[userIndex] << ". Это первый элемент, поэтому перед ним ничего нет, а за ним идет элемент со значением: " << mass[userIndex + 1];
            }
            else {
                cout << "\nВы выбрали элемент под индексом " << userIndex << "\nЕго значение: " << mass[userIndex] << ". Это последний элемент, поэтому после него ничего нет, а за перед идет элемент со значением: " << mass[userIndex - 1];
            }
        }
        else {
            cout << "\nВы выбрали элемент под индексом " << userIndex << "\nЕго значение: " << mass[userIndex] << ". Переред ним идет элемент со значением: " << mass[userIndex - 1] << ", а за ним идет элемент со значением : " << mass[userIndex + 1];
        }
    }
}

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));

    int creating;
    int numSwitch;
    int massCounter;
    List* Head = nullptr;


    int* massiv = 0;


    List* newL = Head;
    
    int* newArray = massiv;

    //cout << sizeof(newArray) << endl;;
    //cout << sizeof(newL) << endl;

    while (true) {

        cout << "\nКакой номер будем решать:\n1 - Задание 1: Создание двусвязного списка\n2 - Задание 2: Замер и сравнение времени создания двусвязного списка и данимического массива\n3 - Задание 3.1: Вставка элемента в двусвязный список\n4 - Задание 3.2: Удаление элемента из двусвязного списка\n5 Задание 3.3: - Обмен двух элементов\n6 - Задание 3.4: Получение информации об элементе\n";
        cout << "7 - Задание 4.1: Замер и сравнение времени всавки элемента в двусвязном списке и данимическоом массиве\n8 - Задание 4.2: Замер и сравнение времени удаления элемента в двусвязном списке и данимическоом массиве\n9 - Задание 4.1: Замер и сравнение времени получения элемента в двусвязном списке и данимическоом массиве\n";
        cin >> numSwitch;

        switch (numSwitch) {

        case 1: {
            int countOfNums;
            cout << "\nКак хотите заполнить массив:\n1 - через размерность\n2 - через ручной ввод (для завершения ввода введите -1000)\n";
            cin >> creating;

            if (creating == 1) {
                cout << "\nВведите размер двусвязного списка: ";
                cin >> countOfNums;
                massCounter = countOfNums;
                Head = createList(countOfNums);
            }
            else {
                Head = createWhile();
            }
            printList(Head);

            break;
        }
        case 2: {
            int vybor;
            int countOfNums;
            cout << "\nДавайте заново создадим список и массив: как будем создавать?\n1 - через размерность\n2 - через while\n";
            cin >> vybor;
            auto startOne = high_resolution_clock::now();
            if (vybor == 1) {
                cout << "\nВведите размер двусвязного списка: ";
                cin >> countOfNums;
                massCounter = countOfNums;
                Head = createList(countOfNums);
            }
            else {
                Head = createWhile();
            }
            auto endOne = high_resolution_clock::now();
            printList(Head);

            auto startTwo = high_resolution_clock::now();
            if (vybor == 1) {
                massiv = createMass(massCounter);
            }
            else {
                cout << "\n(для завершения ввода введите -1000)\n";
                massiv = createWhileMass();
            }

            auto endTwo = high_resolution_clock::now();

            auto durationList = duration_cast<microseconds>(endOne - startOne);
            cout << "Время создания двусвязного списка: " << durationList.count() << " мкс" << endl;
            auto durationMass = duration_cast<microseconds>(endTwo - startTwo);
            cout << "Время создания динамического массива: " << durationMass.count() << " мкс" << endl;

            break;
        }
        case 3:
            if (Head == nullptr) {
                cout << "\nУ вас пустой список\n";
                break;
            }
            vstavka(Head);
            printList(Head);
            break;
        case 4:
            if (Head == nullptr) {
                cout << "\nУ вас пустой список\n";
                break;
            }
            deleting(Head);
            printList(Head);
            break;
        case 5:
            if (Head == nullptr) {
                cout << "\nУ вас пустой список\n";
                break;
            }
            obmen(Head);
            printList(Head);
            break;
        case 6:
            if (Head == nullptr) {
                cout << "\nУ вас пустой список\n";
                break;
            }
            printList(Head);
            poluchenie(Head);
            break;
        case 7: {
            cout << "\nДавайте сравним время выполнения вставки в двусвязном списке и динамическом массиве:\n";
            cout << "Список до вставки:\n";
            printList(Head);
            auto startOne = high_resolution_clock::now();
            vstavka(Head);
            auto endOne = high_resolution_clock::now();
            cout << "Список после вставки:\n";
            printList(Head);
            cout << "\nМассив до вставки:\n";
            printMass(massiv, massCounter);
            auto startTwo = high_resolution_clock::now();
            vstavkaMass(massiv, massCounter);
            auto endTwo = high_resolution_clock::now();
            cout << "Массив после вставки:\n";
            massCounter++;
            printMass(massiv, massCounter);
            auto durationList = duration_cast<microseconds>(endOne - startOne);
            cout << "\nВремя вставки элемента в двусвязный список: " << durationList.count() << " мкс" << endl;
            auto durationMass = duration_cast<microseconds>(endTwo - startTwo);
            cout << "Время вставки элемента в динамический массив: " << durationMass.count() << " мкс" << endl;
            break;
        }
        case 8: {
            cout << "\nДавайте сравним время удаления элемента в двусвязном списке и динамическом массиве:\n";
            cout << "Список до удаления:\n";
            printList(Head);
            auto startOne = high_resolution_clock::now();
            deleting(Head);
            auto endOne = high_resolution_clock::now();
            cout << "Список после удаления:\n";
            printList(Head);
            cout << "\nМассив до удаления:\n";
            printMass(massiv, massCounter);
            auto startTwo = high_resolution_clock::now();
            deleteMass(massiv, massCounter);
            auto endTwo = high_resolution_clock::now();
            cout << "Массив после удаления:\n";
            massCounter--;
            printMass(massiv, massCounter);
            auto durationList = duration_cast<microseconds>(endOne - startOne);
            cout << "\n\nВремя удаления элемента в двусвязном списке: " << durationList.count() << " мкс" << endl;
            auto durationMass = duration_cast<microseconds>(endTwo - startTwo);
            cout << "Время удаления элемента в динамическом массиве: " << durationMass.count() << " мкс" << endl;
            break;
        }
        case 9: {
            cout << "\nДавайте сравним время получения элемента в двусвязном списке и динамическом массиве:\n";
            cout << "Наш список:\n";
            printList(Head);
            auto startOne = high_resolution_clock::now();
            poluchenie(Head);
            auto endOne = high_resolution_clock::now();
            cout << "\nНаш массив:\n";
            printMass(massiv, massCounter);
            auto startTwo = high_resolution_clock::now();
            poluchenieMass(massiv, massCounter);
            auto endTwo = high_resolution_clock::now();
            auto durationList = duration_cast<microseconds>(endOne - startOne);
            cout << "\n\nВремя получения элемента в двусвязном списке: " << durationList.count() << " мкс" << endl;
            auto durationMass = duration_cast<microseconds>(endTwo - startTwo);
            cout << "Время получения элемента в динамическом массиве: " << durationMass.count() << " мкс" << endl;
            break;
        }
        case 0:
            delete Head;
            delete massiv;
            return 0;
        }

    }
}
