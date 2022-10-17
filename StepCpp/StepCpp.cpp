#include <iostream>
#include <string>

using namespace std;

struct Student
{
	char* name{};
	int group{};
};

Student* students = nullptr;
int length{};

void FillStudents();

void WriteToFile();

void ReadFromFile();

void PrintAllStudents();

Student* CreateStudents();

int main()
{
	setlocale(0, "");

	students = CreateStudents();

	FillStudents();
	PrintAllStudents();

	WriteToFile();
	ReadFromFile();

	for (size_t i = 0; i < length; i++)
		delete[] (students + i)->name;

	delete[] students;

	return 0;
}

void FillStudents()
{
	for (int i = 0; i < length; i++)
	{
		char* name = new char[25];
		int group;

		cout << "Enter name:\n";
		cin >> name;

		int len = strlen(name) + 1;
		name[len] = '\0';

		cout << "Enter group:\n";
		cin >> group;

		*(students + i) = Student{ name, group };
	}
}

void WriteToFile()
{
	FILE* stream;

	auto error = fopen_s(&stream, "file.txt", "w");

	if (error != 0) return;

	for (size_t i = 0; i < length; i++)
	{
		auto student = *(students + i);

		fprintf_s(stream, "%s%s%d", student.name, ";", student.group);
		fprintf_s(stream, "\n");
	}

	fclose(stream);
}

void ReadFromFile()
{
	FILE* stream;

	auto error = fopen_s(&stream, "file.txt", "r");

	if (error != 0) return;

	while (!feof(stream))
	{
		auto delimeter = ';';
		auto size = 50;
		auto* buffer = new char[size] {};
		char* pTmp = nullptr;

		fgets(buffer, size, stream);
		auto line = strtok_s(buffer, &delimeter, &pTmp);

		while (line != nullptr)
		{
			cout << "Name: " << line << endl;
			line = strtok_s(nullptr, &delimeter, &pTmp);
			
			cout << "Group: " << line << endl;
			line = strtok_s(nullptr, &delimeter, &pTmp);
		}
	}
}

void PrintAllStudents()
{
	cout << "\n-----Students-----\n";

	for (int i = 0; i < length; i++)
	{
		auto student = *(students + i);

		cout << "Name: " << student.name << ", group: " << student.group << endl;
	}

	cout << "-----End-----\n\n";
}

Student* CreateStudents()
{
	cout << "Enter count students:" << endl;
	cin >> length;

	return new Student[length];
}