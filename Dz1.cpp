#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <fstream>
#include "Header.h"


using namespace std;

errno_t code;

int number = 0;
const int MAX = 25;

void ShowMenu()
{
	cout << "1-Add Person" << endl;

	cout << "2-Show Person" << endl;

	cout << "3-Delete Person" << endl;

	cout << "4-Sort Surname" << endl;

	cout << "5-Search Salary" << endl;

	cout << "6-Search Surname" << endl;
}

bool CheckPhone(char* checkPhone) {
	int size = 0;
	while (checkPhone[size] != '\0')
	{
		if (!isdigit(checkPhone[size]))
		{
			return false;
		}
		size++;
	}

	if (size == 10)
	{
		return true;
	}
	else {
		return false;
	}


}


void AddPerson(Person* person) {
	if (number < MAX)
	{
		Person newperson;
		cout << "Enter People data:" << endl;
		cout << "Name: ";
		cin.ignore();
		cin.getline(newperson.name, sizeof(newperson.name));
		cout << "Surname: ";
		cin.getline(newperson.surname, sizeof(newperson.surname));
		char checkPhone[12];
		do {
			cout << "Phone number (10 symbols): ";
			cin.getline(checkPhone, sizeof(checkPhone));
			if (!CheckPhone(checkPhone))
			{
				cout << "Wrong number" << endl;
			}

		} while (!CheckPhone(checkPhone));
		strcpy_s(newperson.phone, checkPhone);

		cout << "Salary: ";
		cin >> newperson.salary;

		person[number] = newperson;
		number++;
	}
	else {
		cout << "List Full";
	}

}




void AddToFile(const char* filename, Person* person) {
	FILE* PeopleInfo;
	PeopleInfo = fopen(filename, "w");

	if (PeopleInfo == 0)
	{
		cout << "Error";
	}
	else {
		for (int i = 0; i < number; i++)
		{
			fprintf(PeopleInfo, "Name:  %s \n", person[i].name);
			fprintf(PeopleInfo, "Surname:  %s \n", person[i].surname);
			fprintf(PeopleInfo, "Phone:  %s \n", person[i].phone);
			fprintf(PeopleInfo, "Salary:  %lf \n", person[i].salary);
		}
		fclose(PeopleInfo);
	}

}

void ShowPersonData(const char* filename, Person* person) {
	FILE* PeopleInfo;
	code = fopen_s(&PeopleInfo, filename, "r");
	if (!code)
	{
		char buff;
		while ((buff = fgetc(PeopleInfo)) != EOF)
			cout << buff;
	}
	else {
		cout << "Error";

	}
	fclose(PeopleInfo);

}

void ShowPerson(Person* person, int i) {
	cout << "Name: " << person[i].name << endl;
	cout << "Surname: " << person[i].surname << endl;
	cout << "Phone: " << person[i].phone << endl;
	cout << "Salary: " << person[i].salary << endl << endl;
}
void DeletePerson(Person* person)
{
	char surname[20];
	int empt = -1;
	cout << "Enter surname: ";
	cin.ignore();
	cin.getline(surname, sizeof(surname));

	int unswear;
	cout << "Delete(1), or no Delete(2)";
	cin >> unswear;
	switch (unswear)
	{
	case 1:
		for (int i = 0; i < number; i++)
		{
			if (strcmp(person[i].surname, surname) == 0)
			{
				empt = i;
				break;
			}
		}
		if (empt != -1)
		{
			for (int i = empt; i < number - 1; i++)
			{
				person[i] = person[i + 1];
			}
			number--;
			cout << "Data deleted successfully " << endl;
		}
		else {
			cout << "Incorrect surname " << endl;
		}
		break;
	case 2:
		cout << "Stoped delete " << endl;
		break;
	}

}

void SortBySurname(Person* person, const char* filename)
{
	for (size_t i = 0; i < number - 1; i++)
	{
		for (int j = 0; j < number - 1 - i; j++)
		{
			if (strcmp(person[j].surname, person[j + 1].surname) > 0)
			{
				Person change = person[j];
				person[j] = person[j + 1];
				person[j + 1] = change;
			}
		}
	}
	AddToFile(filename, person);
}



void SearchSalary(Person* person)
{
	int salary;
	cout << "Enter look for salary" << endl;
	cin >> salary;
	for (int i = 0; i < number; i++)
	{
		if (salary == person[i].salary)
		{
			ShowPerson(person, i);
		}
	}
}
void SearchSurname(Person* person)
{
	char surname[25];
	cout << "Enter look for surname" << endl;
	cin.ignore();
	cin.getline(surname, sizeof(surname));
	for (int i = 0; i < number; i++)
	{
		if (strcmp(surname,  person[i].surname) == 0)
		{
			ShowPerson(person, i);
		}
	}
}


int main()
{
	const char* filename = "person.txt";

	Person* person = new Person[MAX];
	int choice;
	ShowMenu();
	bool contin = false;


	do {
		cout << "Enter Choice" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:

			AddPerson(person);
			AddToFile(filename, person);
			break;

		case 2:

			ShowPersonData(filename, person);
			break;

		case 3:

			DeletePerson(person);
			AddToFile(filename, person);
			break;
		case 4:
			SortBySurname(person, filename);
			break;
		case 5:
			SearchSalary(person);
			break;
		case 6:
			SearchSurname(person);
			break;
		}
		cout << "Continue(1)? Stop(0):  ";
		cin >> contin;

	} while (contin);


}