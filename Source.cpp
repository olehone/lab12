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

// ��������� �������
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
        cout << "������ ��� ����: ";
        cin >> choice;
        processMenuChoice(L, choice);
    } while (choice != 0);
    return 0;
}
void addFlight(Elem*& L)
{
    Info newFlight;

    cout << "������ ����� �����: ";
    cin >> newFlight.flightNumber;

    cout << "������ ����� �����������: ";
    cin >> newFlight.destination;

    cout << "������ ������� �� ������� ��������: ";
    cin.ignore();  // ���������� ������ ������ ����� ���� �������� ������ �����
    getline(cin, newFlight.passengerName);

    cout << "������ ��, ����� �� ���� �������: ";
    cin >> newFlight.year >> newFlight.month >> newFlight.day;

    enqueue(L, newFlight);  // ��������� ������ ����� �� ������
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
                // ���� ������� �� �������� ��������� �� ���������
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
        cout << "������� �������� ����� ��� ������." << endl;
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
        cout << "������� �������� ����� ��� �������." << endl;
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
        inputFile.ignore();  // ���������� ������ ������ �����
        getline(inputFile, passengerName);
        inputFile >> year;
        inputFile >> month;
        inputFile >> day;
        inputFile.ignore();  // ���������� ������ ������ �����

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

    cout << "������ ����� �����������: ";
    cin.ignore();
    getline(cin, info.destination);

    cout << "������ ����� �����: ";
    cin >> info.flightNumber;

    cout << "������ ������� � ������� ��������: ";
    cin.ignore();
    getline(cin, info.passengerName);

    cout << "������ �� �������: ";
    cin >> info.year;

    cout << "������ ����� �������: ";
    cin >> info.month;

    cout << "������ ���� �������: ";
    cin >> info.day;

    enqueue(L, info);

    cout << "������ ������ ������." << endl;
}
void removeRequest(Elem*& L)
{
    if (L == NULL)
    {
        cout << "������ ������ �������." << endl;
        return;
    }

    int flightNumber;
    int year;
    int month;
    int day;

    cout << "������ ����� �����: ";
    cin >> flightNumber;

    cout << "������ �� �������: ";
    cin >> year;

    cout << "������ ����� �������: ";
    cin >> month;

    cout << "������ ���� �������: ";
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
                L->prev = toDelete->prev; // ��������� ��������� �� ������� �������
                toDelete->prev->next = L; // ��������� ��������� � ������������ ��������
            }
            else
            {
                L = NULL;
            }
        }

        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;

        delete toDelete;

        cout << "������ ��������." << endl;
    }
    else
    {
        cout << "������ �� ��������." << endl;
    }
}
void printRequests(Elem* L)
{
    if (L == NULL)
    {
        cout << "������ ������ �������." << endl;
        return;
    }

    Elem* current = L;
    do {
        cout << "����� �����������: " << current->info.destination << endl;
        cout << "����� �����: " << current->info.flightNumber << endl;
        cout << "������� � ������� ��������: " << current->info.passengerName << endl;
        cout << "���� �������: " << current->info.day << "." << current->info.month << "." << current->info.year << endl;
        cout << endl;
        current = current->next;
    } while (current != L);
}

void printRequestsByFlightAndDate(Elem* L, int flightNumber, int year, int month, int day)
{
    if (L == NULL)
    {
        cout << "������ ������ �������." << endl;
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
            cout << "����� �����������: " << current->info.destination << endl;
            cout << "����� �����: " << current->info.flightNumber << endl;
            cout << "������� � ������� ��������: " << current->info.passengerName << endl;
            cout << "���� �������: " << current->info.day << "." << current->info.month << "." << current->info.year << endl;
            cout << endl;
            found = true;
        }
        current = current->next;
    } while (current != L);

    if (!found)
    {
        cout << "������ � ����� ������� ����� �� ����� ������� �� ��������." << endl;
    }
}

void printMenu()
{
    cout << "����:" << endl;
    cout << "1. ������ ������" << endl;
    cout << "2. �������� ������" << endl;
    cout << "3. ������� �� ������" << endl;
    cout << "4. ������� ������ �� ������� ����� �� ����� �������" << endl;
    cout << "5. ����������� ������ � �����" << endl;
    cout << "6. ����������� ������ � ����" << endl;
    cout << "7. �����������" << endl;
    cout << "0. ����� � ��������" << endl;
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
        cout << "������ ����� �����: ";
        cin >> flightNumber;
        cout << "������ �� �������: ";
        cin >> year;
        cout << "������ ����� �������: ";
        cin >> month;
        cout << "������ ���� �������: ";
        cin >> day;
        printRequestsByFlightAndDate(L, flightNumber, year, month, day);
        break;
    case 5:
    {
        string fileName = "default.txt";
        cout << "������ ��'� �����: ";
        cin >> fileName;
        L = loadFromFile(fileName);
        break;
    }
    case 6:
    {
        string fileName2 = "default.txt";
        cout << "������ ��'� �����: ";
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
        cout << "����� �� ������������ ��������!" << endl;
        break;
    default:
        cout << "������������ ����. ��������� �� ���." << endl;
        break;
    }
}
