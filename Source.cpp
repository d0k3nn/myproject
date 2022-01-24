#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>

using namespace std;
double All_SUM = 0;
int global_id = 0;

class Product
{
private:
    int id;
    int day;
    int month;
    int year;
    int allsum;
public:

    char name[20];
    char description[128];
    char last_time[20];

    void CreateItem(Product& obj)
    {
        global_id++;
        obj.id = global_id;
        system("cls");
        cin.ignore();
        cout << "������� �������� ������ ���� ";
        cin.getline(obj.name, 20);
        cout << "������� ����(� ������� ��) ";
        cin >> obj.day;
        if (obj.day > 31)
        {
            cout << "�� ����� ������������ �����\n";
            cout << "������� ����(� ������� ��) ";
            cin >> obj.day;
        }
        else if (obj.day <= 0)
        {
            cout << "�� ����� ������������ �����\n";
            cout << "������� ����(� ������� ��) ";
            cin >> obj.day;
        }
        cout << "������� �����(� ������� ��) ";
        cin >> obj.month;
        if (obj.month > 12)
        {
            cout << "�� ����� ������������ �����\n";
            cout << "������� �����(� ������� ��) ";
            cin >> obj.month;
        }
        else if (obj.month <= 0)
        {
            cout << "�� ����� ������������ �����\n";
            cout << "������� �����(� ������� ��) ";
            cin >> obj.month;
        }
        cout << "������� ���(� ������� ����) ";
        cin >> obj.year;
        if (obj.year <= 999)
        {
            cout << "�� ����� ������������ �����\n";
            cout << "������� ���(� ������� ����) ";
            cin >> obj.year;
        }
        else if (obj.year >= 10000)
        {
            cout << "�� ����� ������������ �����\n";
            cout << "������� ���(� ������� ����) ";
            cin >> obj.year;
        }
        cin.ignore();
        cout << "������� ������� �������� ������ ���� ";
        cin.getline(obj.description, 128);
        cout << "������� ���� ���������� ����� ���� (� ������� ��.��.��) ";
        cin.getline(obj.last_time, 20);
    }
    void AddItem(Product*& obj, int& size)
    {
        size++;
        Product* buf = new Product[size];
        for (int i = 0; i < size; i++)
        {
            if (i < size - 1)
            {
                buf[i] = obj[i];
            }
            else if (i == size - 1)
            {
                CreateItem(buf[i]);
            }
        }
        obj = nullptr;
        obj = new Product[size];
        obj = buf;
        buf = nullptr;
    }
    void Create(Product*& obj, int& size)
    {
        obj = new Product[size];
    }
    void PrintItem(Product obj)
    {
        cout << "��������: " << obj.name << endl;
        cout << "����: " << obj.day << endl;
        cout << "�����: " << obj.month << endl;
        cout << "���: " << obj.year << endl;
        cout << "��������: " << obj.description << endl;
        cout << "���� ���������� ������ ���� => " << obj.last_time << endl;
    }
    void Print(Product* obj, int size)
    {
        system("cls");
        for (size_t i = 0; i < size; i++)
        {
            cout << "���� #" << obj[i].id << endl;
            PrintItem(obj[i]);
            cout << endl;
        }
    }
    void Delete(Product*& obj, int& size)
    {
        Print(obj, size);
        cout << "������� ����� ����, ��� �������� ";
        int index;
        cin >> index;
        int k = 0;
        Product* buf = new Product[size - 1];
        for (int i = 0; i < size - 1; i++)
        {
            if (obj[i].id < index)
            {
                buf[k] = obj[i];
                k++;
            }
            else if (obj[i].id == index)
            {
                All_SUM = All_SUM + obj[i].day;
                buf[k] = obj[i + 1];
                k++;
            }
            else
            {
                buf[k] = obj[i + 1];
                k++;
            }
        }
        size--;
        obj = nullptr;
        obj = new Product[size];
        obj = buf;
        buf = nullptr;
    }
    void Save(Product* array, int size)
    {
        fstream file;
        file.open("List of tasks.bin", ios::out | ios::binary);
        if (file.is_open())
        {
            file.write((char*)&size, sizeof(size));
            file.write((char*)array, size * sizeof(Product));
            file.close();
        }
        else
        {
            perror("Error occured while opening file");
        }
    }
    void Load(Product*& array, int& size)
    {
        fstream file;
        file.open("List of tasks.bin", ios::in | ios::binary);
        if (file.is_open())
        {
            file.read((char*)&size, sizeof(size));
            array = new Product[size]{};
            file.read((char*)array, size * sizeof(Product));
            file.close();
        }
        else
        {
            perror("Error occured while opening file");
        }
    }
    void Sort(Product* product, int n)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (product[i].day >= product[j].day && product[i].month >= product[j].month && product[i].year >= product[j].year)
                {
                    Product temp = product[j];
                    product[j] = product[i];
                    product[i] = temp;
                }
            }
        }
    }
    void Search(Product* obj, int size)
    {
        int poisk;
        cout << "������� ������� ����\n";
        cin >> poisk;
        if (poisk == obj->day)
        {
            Print(obj, size);
        }
    }
};


void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    Product* product = nullptr;
    Product pr;
    int size = 0;

    int switch_on, check = 0;
    cout << "1 - ������� ����� ������" << endl;
    cout << "2 - ��������� ������" << endl;
    cout << "����: ";
    cin >> check;
    if (check == 1)
    {
        pr.Create(product, size);
    }
    else if (check == 2)
    {
        pr.Load(product, size);
    }
    do
    {
        system("cls");
        cout << "1 - �������� ����" << endl;
        cout << "2 - ���������� ����(�)" << endl;
        cout << "3 - ��������� ����(�) � ���� ������� .bin" << endl;
        cout << "4 - ������� ���� ����" << endl;
        cout << "5 - ������� ��� ����" << endl;
        cout << "6 - ������������� ���� �� �������(������� ������)" << endl;
        cout << "7 - ����� �� ��������/��������/������� ����������" << endl;
        cout << "8 - ����������� ��� � ����������� ����" << endl;
        cout << "\t\n\t\t������� �����-������ ������� ��� ������" << endl;
        cout << "����: ";

        cin >> switch_on;
        switch (switch_on)
        {
        case 1:
        {
            pr.AddItem(product, size);
            cout << "���� ������� ���������!" << endl;
            system("pause");
        }break;
        case 2:
        {
            if (size != 0)
            {
                pr.Print(product, size);
                system("pause");
            }
            else
            {
                cout << "������ ����!" << endl;
                system("pause");
            }
        }break;
        case 3:
        {
            pr.Save(product, size);
            cout << sizeof(Product) << endl;
            cout << "������ �������!" << endl;
            system("pause");
        }break;
        case 4:
        {
            if (size != 0)
            {
                pr.Delete(product, size);
                system("pause");
            }
            else
            {
                cout << "������ ����!" << endl;
                system("pause");
            }
        }break;
        case 5:
        {
            size = 0;
            product = nullptr;
            cout << "������ �����!" << endl;
            system("pause");
        }break;

        case 6:
        {
            pr.Sort(product, size);
            cout << "\t���������� ������� ���������\n" << endl;
            system("pause");
        }break;
        case 7:
        {
            int poisk;
            cout << "\t1 - ����� �� ����� ����\n";
            cout << "\t2 - ����� �� ������� ���������� ����\n";
            cout << "\t3 - ����� �� �������� ����\n";
            cout << "����: ";

            cin >> poisk;
            switch (poisk)
            {
            case 1:
                char d[30];
                cout << "������� �������� ����" << endl;
                cin.ignore();
                cin.getline(d, 30);
                for (int i = 0; i < size; i++)
                {
                    if (strcmp(d, product[i].name) == 0)
                    {
                        pr.Print(product, size);
                        system("pause");
                    }
                }
                break;
            case 2:
                char c[30];
                cout << "������� ����� ���������� ����" << endl;
                cin.ignore();
                cin.getline(c, 30);
                for (int i = 0; i < size; i++)
                {
                    if (strcmp(c, product[i].last_time) == 0)
                    {
                        pr.Print(product, size);
                        system("pause");
                    }
                }
                break;
            case 3:
                char b[128];
                cout << "������� �������� ����" << endl;
                cin.ignore();
                cin.getline(b, 128);
                for (int i = 0; i < size; i++)
                {
                    if (strcmp(b, product[i].description) == 0)
                    {
                        pr.Print(product, size);
                        system("pause");
                    }
                }
            }
        }break;
        case 8:
        {
            pr.Search(product, size);
        }break;
        default:
            exit(0);
            break;
        }
    } while (true);
}