#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

struct Info
{
    string destination;
    int flightNumber;
    string passengerName;
    int year;
    int month;
    int day;
};

struct Elem
{
    Elem* next;
    Elem* prev;
    Info info;
};

// Прототипи функцій
void enqueue(Elem*& L, Info value);
void saveToFile(Elem* L, const string& fileName);
void addFlight(Elem*& L);
Elem* loadFromFile(const string& fileName);
void addRequest(Elem*& L);
void removeRequest(Elem*& L);
void printRequests(Elem* L);
void printRequestsByFlightAndDate(Elem* L, int flightNumber, int year, int month, int day);
void printMenu();
void processMenuChoice(Elem*& L, int choice);
void bubbleSortByFlightNumber(Elem*& L);
int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    Elem* L = NULL;

    int choice;
    do {
        printMenu();
        cout << "Введіть свій вибір: ";
        cin >> choice;
        processMenuChoice(L, choice);
    } while (choice != 0);
    return 0;
}
void addFlight(Elem*& L)
{
    Info newFlight;

    cout << "Введіть номер рейсу: ";
    cin >> newFlight.flightNumber;

    cout << "Введіть пункт призначення: ";
    cin >> newFlight.destination;

    cout << "Введіть прізвище та ініціали пасажира: ";
    cin.ignore();  // Пропускаємо символ нового рядка після введення номера рейсу
    getline(cin, newFlight.passengerName);

    cout << "Введіть рік, місяць та день вильоту: ";
    cin >> newFlight.year >> newFlight.month >> newFlight.day;

    enqueue(L, newFlight);  // Додавання нового рейсу до списку
}

void bubbleSortByFlightNumber(Elem*& L)
{
    if (L == NULL || L->next == L)
        return;

    bool swapped;
    do {
        swapped = false;
        Elem* current = L;
        while (current->next != L) {
            if (current->info.flightNumber > current->next->info.flightNumber) {
                // Обмін значень між поточним елементом та наступним
                Info temp = current->info;
                current->info = current->next->info;
                current->next->info = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void enqueue(Elem*& L, Info value)
{
    Elem* tmp = new Elem;
    tmp->info = value;

    if (L == NULL)
    {
        L = tmp;
        L->prev = L;
        L->next = L;
    }
    else
    {
        Elem* prevL = L->prev;
        prevL->next = tmp;
        tmp->prev = prevL;
        tmp->next = L;
        L->prev = tmp;
    }
}

void saveToFile(Elem* L, const string& fileName)
{
    ofstream outputFile(fileName);
    if (!outputFile)
    {
        cout << "Помилка відкриття файлу для запису." << endl;
        return;
    }

    Elem* current = L;
    do {
        outputFile << current->info.destination << endl;
        outputFile << current->info.flightNumber << endl;
        outputFile << current->info.passengerName << endl;
        outputFile << current->info.year << endl;
        outputFile << current->info.month << endl;
        outputFile << current->info.day << endl;
        current = current->next;
    } while (current != L);

    outputFile.close();
}

Elem* loadFromFile(const string& fileName)
{
    Elem* L = NULL;

    ifstream inputFile(fileName);
    if (!inputFile)
    {
        cout << "Помилка відкриття файлу для читання." << endl;
        return NULL;
    }

    string destination;
    int flightNumber;
    string passengerName;
    int year;
    int month;
    int day;

    while (getline(inputFile, destination))
    {
        inputFile >> flightNumber;
        inputFile.ignore();  // Пропустити символ нового рядка
        getline(inputFile, passengerName);
        inputFile >> year;
        inputFile >> month;
        inputFile >> day;
        inputFile.ignore();  // Пропустити символ нового рядка

        Info info;
        info.destination = destination;
        info.flightNumber = flightNumber;
        info.passengerName = passengerName;
        info.year = year;
        info.month = month;
        info.day = day;

        enqueue(L, info);
    }

    inputFile.close();

    return L;
}

void addRequest(Elem*& L)
{
    Info info;

    cout << "Введіть пункт призначення: ";
    cin.ignore();
    getline(cin, info.destination);

    cout << "Введіть номер рейсу: ";
    cin >> info.flightNumber;

    cout << "Введіть прізвище і ініціали пасажира: ";
    cin.ignore();
    getline(cin, info.passengerName);

    cout << "Введіть рік вильоту: ";
    cin >> info.year;

    cout << "Введіть місяць вильоту: ";
    cin >> info.month;

    cout << "Введіть день вильоту: ";
    cin >> info.day;

    enqueue(L, info);

    cout << "Заявка успішно додана." << endl;
}
void removeRequest(Elem*& L)
{
    if (L == NULL)
    {
        cout << "Список заявок порожній." << endl;
        return;
    }

    int flightNumber;
    int year;
    int month;
    int day;

    cout << "Введіть номер рейсу: ";
    cin >> flightNumber;

    cout << "Введіть рік вильоту: ";
    cin >> year;

    cout << "Введіть місяць вильоту: ";
    cin >> month;

    cout << "Введіть день вильоту: ";
    cin >> day;

    Elem* current = L;
    Elem* toDelete = NULL;
    bool found = false;

    do {
        if (current->info.flightNumber == flightNumber &&
            current->info.year == year &&
            current->info.month == month &&
            current->info.day == day)
        {
            toDelete = current;
            found = true;
            break;
        }
        current = current->next;
    } while (current != L);

    if (found)
    {
        if (toDelete == L)
        {
            if (L->next != L)
            {
                L = L->next;
                L->prev = toDelete->prev; // Оновлення посилання на останній елемент
                toDelete->prev->next = L; // Оновлення посилання з попереднього елемента
            }
            else
            {
                L = NULL;
            }
        }

        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;

        delete toDelete;

        cout << "Заявка видалена." << endl;
    }
    else
    {
        cout << "Заявка не знайдена." << endl;
    }
}
void printRequests(Elem* L)
{
    if (L == NULL)
    {
        cout << "Список заявок порожній." << endl;
        return;
    }

    Elem* current = L;
    do {
        cout << "Пункт призначення: " << current->info.destination << endl;
        cout << "Номер рейсу: " << current->info.flightNumber << endl;
        cout << "Прізвище і ініціали пасажира: " << current->info.passengerName << endl;
        cout << "Дата вильоту: " << current->info.day << "." << current->info.month << "." << current->info.year << endl;
        cout << endl;
        current = current->next;
    } while (current != L);
}

void printRequestsByFlightAndDate(Elem* L, int flightNumber, int year, int month, int day)
{
    if (L == NULL)
    {
        cout << "Список заявок порожній." << endl;
        return;
    }

    Elem* current = L;
    bool found = false;

    do {
        if (current->info.flightNumber == flightNumber &&
            current->info.year == year &&
            current->info.month == month &&
            current->info.day == day)
        {
            cout << "Пункт призначення: " << current->info.destination << endl;
            cout << "Номер рейсу: " << current->info.flightNumber << endl;
            cout << "Прізвище і ініціали пасажира: " << current->info.passengerName << endl;
            cout << "Дата вильоту: " << current->info.day << "." << current->info.month << "." << current->info.year << endl;
            cout << endl;
            found = true;
        }
        current = current->next;
    } while (current != L);

    if (!found)
    {
        cout << "Заявка з таким номером рейсу та датою вильоту не знайдена." << endl;
    }
}

void printMenu()
{
    cout << "Меню:" << endl;
    cout << "1. Додати заявку" << endl;
    cout << "2. Видалити заявку" << endl;
    cout << "3. Вивести всі заявки" << endl;
    cout << "4. Вивести заявки за номером рейсу та датою вильоту" << endl;
    cout << "5. Завантажити заявки з файлу" << endl;
    cout << "6. Завантажити заявки в файл" << endl;
    cout << "7. Посортувати" << endl;
    cout << "0. Вийти з програми" << endl;
}

void processMenuChoice(Elem*& L, int choice)
{
    switch (choice)
    {
    case 1:
        addRequest(L);
        break;
    case 2:
        removeRequest(L);
        break;
    case 3:
        printRequests(L);
        break;
    case 4:
        int flightNumber, year, month, day;
        cout << "Введіть номер рейсу: ";
        cin >> flightNumber;
        cout << "Введіть рік вильоту: ";
        cin >> year;
        cout << "Введіть місяць вильоту: ";
        cin >> month;
        cout << "Введіть день вильоту: ";
        cin >> day;
        printRequestsByFlightAndDate(L, flightNumber, year, month, day);
        break;
    case 5:
    {
        string fileName = "default.txt";
        cout << "Введіть ім'я файлу: ";
        cin >> fileName;
        L = loadFromFile(fileName);
        break;
    }
    case 6:
    {
        string fileName2 = "default.txt";
        cout << "Введіть ім'я файлу: ";
        cin >> fileName2;
        saveToFile(L, fileName2);
        break;
    }
    case 7:
    {
        bubbleSortByFlightNumber(L);
        break;
    }
    case 0:
        cout << "Дякую за використання програми!" << endl;
        break;
    default:
        cout << "Неправильний вибір. Спробуйте ще раз." << endl;
        break;
    }
}
