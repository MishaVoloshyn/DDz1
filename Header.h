#pragma once

struct Person {

	char name[20 ];
	char surname[25];
	char phone[20];
	double salary;

};

void ShowMenu();

void AddPerson(Person* person);

void AddToFile(const char* filename, Person* person);

void ShowPersonData(const char* filename, Person* person);

void SearchSalary(Person* person);

void SearchSurname(Person* person);

void SortBySurname(Person* person, const char* filename);

void DeletePerson(Person* person);

bool CheckPhone(char* checkPhone);

