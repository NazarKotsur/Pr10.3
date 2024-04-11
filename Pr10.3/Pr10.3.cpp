#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

const int MAX_PRODUCTS = 100;

struct Tovar {
    string nazva;
    double vartis;
    int kilkist;
    string odun_vum;
};

void Create(Tovar tovary[], int& n);
void Print(const Tovar tovary[], int n);
void SearchTovarByName(const Tovar tovary[], int n);
void SearchTovarByRange(const Tovar tovary[], int n);
void SaveToFile(const Tovar tovary[], int n, const string& filename);
void LoadFromFile(Tovar tovary[], int& n, const string& filename);
bool IsValidNumber(const string& str);
bool IsValidDouble(const string& str);
bool IsValidInteger(const string& str);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Tovar tovary[MAX_PRODUCTS];
    int n = 0;
    string filename;

    cout << "������ ��'� �����: ";
    cin >> filename;

    LoadFromFile(tovary, n, filename);

    int menuItem;
    do {
        cout << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - ���� ������ �� �����" << endl;
        cout << " [2] - ��������� ������ ������" << endl;
        cout << " [3] - ����� ������ �� ������" << endl;
        cout << " [4] - ����� ������ �� ��������� �������" << endl;
        cout << " [0] - �������� �� �����" << endl << endl;
        cout << "������ ��������: ";
        cin >> menuItem;
        cout << endl << endl;

        switch (menuItem) {
        case 1:
            Print(tovary, n);
            break;
        case 2:
            Create(tovary, n);
            break;
        case 3:
            SearchTovarByName(tovary, n);
            break;
        case 4:
            SearchTovarByRange(tovary, n);
            break;
        case 0:
            SaveToFile(tovary, n, filename);
            break;
        default:
            cout << "�� ����� ��������� ��������! "
                "��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (menuItem != 0);

    return 0;
}

void Create(Tovar tovary[], int& n) {
    if (n >= MAX_PRODUCTS) {
        cout << "���������� ����������� ������� ������." << endl;
        return;
    }

    cout << "����� ������: "; cin >> tovary[n].nazva;
    cout << "������� ������ �� ������� ������: ";
    string vartisInput;
    cin >> vartisInput;
    while (!IsValidDouble(vartisInput)) {
        cout << "������� ���������� �������. ��������� �� ���: ";
        cin >> vartisInput;
    }
    tovary[n].vartis = stod(vartisInput);

    cout << "ʳ������ ������: ";
    string kilkistInput;
    cin >> kilkistInput;
    while (!IsValidInteger(kilkistInput)) {
        cout << "������� ���������� �������. ��������� �� ���: ";
        cin >> kilkistInput;
    }
    tovary[n].kilkist = stoi(kilkistInput);

    cout << "������� ����������: "; cin >> tovary[n].odun_vum;
    n++;
}

void Print(const Tovar tovary[], int n) {
    if (n == 0) {
        cout << "������ ������ �������." << endl;
        return;
    }

    cout << "=========================================================="
        << endl;
    cout << "| � | ����� ������ | ������� | ʳ������ | ������� ���. |"
        << endl;
    cout << "----------------------------------------------------------"
        << endl;

    for (int i = 0; i < n; ++i) {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << tovary[i].nazva
            << "| " << setw(8) << right << fixed << setprecision(2) << tovary[i].vartis << " "
            << "| " << setw(9) << left << tovary[i].kilkist << " "
            << "| " << setw(12) << left << tovary[i].odun_vum << " |" << endl;
    }
    cout << "=========================================================="
        << endl;
    cout << endl;
}

void SearchTovarByName(const Tovar tovary[], int n) {
    if (n == 0) {
        cout << "������ ������ �������." << endl;
        return;
    }

    string nazva;
    cout << "������ ����� ������: ";
    cin >> nazva;

    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (tovary[i].nazva == nazva) {
            cout << "����� ��������:" << endl;
            cout << "| ����� ������ | ������� | ʳ������ | ������� ���. |" << endl;
            cout << "| " << setw(13) << left << tovary[i].nazva
                << "| " << setw(8) << right << fixed << setprecision(2) << tovary[i].vartis << " "
                << "| " << setw(9) << left << tovary[i].kilkist << " "
                << "| " << setw(14) << left << tovary[i].odun_vum << " |" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "������ ������ ���� � ����������" << endl;
    }
}

void SearchTovarByRange(const Tovar tovary[], int n) {
    if (n == 0) {
        cout << "������ ������ �������." << endl;
        return;
    }

    double minPrice, maxPrice;
    cout << "������ ������� ������� ������ (�������� �� ����������� ����): ";
    string minPriceInput, maxPriceInput;
    cin >> minPriceInput >> maxPriceInput;

    while (!IsValidDouble(minPriceInput) || !IsValidDouble(maxPriceInput) || stod(minPriceInput) >= stod(maxPriceInput)) {
        cout << "������� ����������� �������. ��������� �� ���: ";
        cin >> minPriceInput >> maxPriceInput;
    }

    minPrice = stod(minPriceInput);
    maxPrice = stod(maxPriceInput);

    cout << "������ � ������� � ������� [" << minPrice << ", " << maxPrice << "]:" << endl;
    cout << "| ����� ������ | ������� | ʳ������ | ������� ���. |" << endl;
    for (int i = 0; i < n; ++i) {
        double totalValue = tovary[i].vartis * tovary[i].kilkist;
        if (totalValue >= minPrice && totalValue <= maxPrice) {
            cout << "| " << setw(13) << left << tovary[i].nazva
                << "| " << setw(8) << right << fixed << setprecision(2) << tovary[i].vartis << " "
                << "| " << setw(9) << left << tovary[i].kilkist << " "
                << "| " << setw(14) << left << tovary[i].odun_vum << " |" << endl;
        }
    }
}

void SaveToFile(const Tovar tovary[], int n, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < n; ++i) {
            file << tovary[i].nazva << "," << tovary[i].vartis << "," << tovary[i].kilkist << "," << tovary[i].odun_vum << endl;
        }
        file.close();
        cout << "������ ������ ��������� � ���� " << filename << endl;
    }
    else {
        cout << "������� �������� ����� ��� ������." << endl;
    }
}

void LoadFromFile(Tovar tovary[], int& n, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line) && n < MAX_PRODUCTS) {
            size_t pos = 0;
            pos = line.find(',');
            tovary[n].nazva = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            tovary[n].vartis = stod(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find(',');
            tovary[n].kilkist = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            tovary[n].odun_vum = line;
            n++;
        }
        file.close();
        cout << "������ ������ ����������� � ����� " << filename << endl;
    }
    else {
        cout << "���� " << filename << " �� ��������. ����� ������ ���� ��������." << endl;
    }
}

bool IsValidNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}

bool IsValidDouble(const string& str) {
    if (str.empty()) {
        return false;
    }

    int dotCount = 0;
    for (char c : str) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
        if (c == '.') {
            dotCount++;
        }
    }

    return dotCount <= 1;
}

bool IsValidInteger(const string& str) {
    if (str.empty()) {
        return false;
    }

    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }

    return true;
}