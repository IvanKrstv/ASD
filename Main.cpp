#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include "help_functions.h"
using namespace std;

struct Participants {
	int number, age;
	char name[80];
	float results;
	Participants* next;
}*start = NULL;

const int max_participants_size = 30;
const char text_file[] = "participants.txt";

const int no_column_width = 5;
const int age_column_width = 5;
const int results_column_width = 9;
const int table_width_without_name = no_column_width + age_column_width + results_column_width;


void Input(int& size, int& max_name);

void Output(int size, int max_name);

void SubMenu(Participants participants[], int size, int max_name);
void SearchYoungest(Participants participants[], int size);
void SearchByName(Participants participants[], int size, int max_name);

void SortByAge(Participants participants[], int size);

void AdditionalFunctions(Participants participants[], int size, int max_name);
void SortByAgeWithoutChanging(Participants participants[], int size, int max_name);
void SearchByAge(Participants participants[], int size, int max_name);
void SearchByGender(Participants participants[], int size, int max_name);


void HeaderRowOfTable(int max_name);
void TitleRowOfTable(int max_name);
void BodyOfTable(Participants* participant, int size, int max_name, int i);

bool CheckParticipantsEntered(bool entered);
void CheckMaxName(Participants* participant, int& max_name);
void AutoInput(Participants* participant, int& size, int& max_name, bool& entered);

Participants* insertAtEnd(Participants* head_ref, Participants* new_participant);


int main()
{
	int choice;
	bool exit = false;
	bool entered_participants = false;

	int size = 0;

	int max_name = 0;
	AutoInput(start, size, max_name, entered_participants);
	do
	{
		cout << "Beauty contest" << endl;
		cout << endl;
		cout << "1. Add new participants;" << endl;
		cout << "2. Display all participants;" << endl;
		cout << "3. Search participants;" << endl;
		cout << "4. Sort the participants in ascending order by their age;" << endl;
		cout << "5. Additional actions;" << endl;
		cout << "6. Exit." << endl;
		cout << "\nEnter your choice: "; cin >> choice;
		if (!CheckCin())
			continue;
		cout << endl;

		if (choice >= 1 && choice <= 6)
		{
			switch (choice)
			{
			case 1: Input(size, max_name);
				entered_participants = true;
				break;

			case 2: if (CheckParticipantsEntered(entered_participants))
			{
				Output(size, max_name);
				system("pause");
			}
				  break;

			case 3: if (CheckParticipantsEntered(entered_participants))
			{
				system("cls");
				SubMenu(participants, size, max_name);
			}
				  break;

			case 4: if (CheckParticipantsEntered(entered_participants))
				SortByAge(participants, size);
				break;


			case 5: if (CheckParticipantsEntered(entered_participants))
			{
				system("cls");
				AdditionalFunctions(participants, size, max_name);
			}
				  break;

			case 6: exit = true;
				break;
			}
		}
		else
		{
			cout << "Invalid choice! Try again!" << endl;
			system("pause");
		}
		system("cls");
	} while (!exit);

	return 0;
}


void Input(int& size, int& max_name)
{
	int new_participants;

	cout << "How many new participants would you like to add? ";
	cin >> new_participants;
	cout << endl;
	if (new_participants > max_participants_size - size)
		cout << "There are not enough places left. You can add only up to " << max_participants_size - size << " participants more." << endl;
	else
	{
		for (int i = 0; i < new_participants; i++)
		{
			Participants* new_participant = new Participants;
			cout << "Participant No. " << size + 1 << ':' << endl;
			cout << endl;

			cout << "Number: "; cin >> new_participant->number;
			if (!CheckCin())
				return;

			ClearBuffer();
			cout << "Name: "; cin.getline(new_participant->name, 79);
			CheckMaxName(new_participant, max_name);

			cout << "Age: "; cin >> new_participant->age;
			if (!CheckCin())
				return;

			cout << "Result: "; cin >> new_participant->results;
			if (!CheckCin())
				return;

			ClearBuffer();
			insertAtEnd(start, new_participant);

			cout << endl;
			size++;
		}
	}
}


void Output(int size, int max_name)
{
	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	Participants* temp = start;
	for (int i = 0; i < size; i++)
	{
		BodyOfTable(temp, size, max_name, i);
		temp = temp->next;
	}
}


void SubMenu(Participants participants[], int size, int max_name)
{
	int choice;
	bool back = false;
	do
	{
		cout << "1. Search youngest participants;" << endl;
		cout << "2. Search by name;" << endl;
		cout << "3. Back" << endl;
		cout << "\nEnter your choice: "; cin >> choice;

		if (!CheckCin())
			continue;
		cout << endl;

		if (choice >= 1 && choice <= 3)
		{
			switch (choice)
			{
			case 1: SearchYoungest(participants, size);
				PressEnterToContinue();
				break;
			case 2: SearchByName(participants, size, max_name);
				PressEnterToContinueAfterIgnore();
				break;
			case 3: back = true;
				break;
			}
		}
		else
		{
			cout << "No such choice!" << endl;
			PressEnterToContinue();
		}
		system("cls");
	} while (!back);
}
void SearchYoungest(Participants participants[], int size)
{
	int min_age = participants[0].age, counter = 0;

	for (int i = 1; i < size; i++)
	{
		if (participants[i].age < min_age)
			min_age = participants[i].age;
	}

	for (int j = 0; j < size; j++)
	{
		if (participants[j].age == min_age)
		{
			if (counter >= 1)
				cout << ", ";
			cout << participants[j].name;
			counter++;
		}
	}

	cout << endl;
	if (counter > 1)
		cout << "These participants are " << min_age << " years old." << endl;
	else cout << "The participant is " << min_age << " years old." << endl;
}
void SearchByName(Participants participants[], int size, int max_name)
{
	char target_name[80]; bool found = false;

	cout << "Name: ";
	ClearBuffer();
	cin.getline(target_name, 79);

	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	for (int i = 0; i < size; i++)
	{
		if (strcmp(target_name, participants[i].name) == 0)
		{
			found = true;
			BodyOfTable(participants, size, max_name, i);
		}
	}

	if (!found)
		cout << "No participant with such name." << endl;
}


void SortByAge(Participants participants[], int size)
{
	Participants temp;
	bool swap = false;
	for (int i = 0; i < size - 1; i++)
	{
		swap = false;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (participants[j].age > participants[j + 1].age)
			{
				temp = participants[j];
				participants[j] = participants[j + 1];
				participants[j + 1] = temp;
				swap = true;
			}
		}
		if (!swap)
			break;
	}
}



void AdditionalFunctions(Participants participants[], int size, int max_name)
{
	int choice; bool back = false;
	do
	{
		cout << "1. Display all participants sorted by age;" << endl;
		cout << "2. Search by age;" << endl;
		cout << "3. Search by gender;" << endl;
		cout << "4. Back" << endl;
		cout << "\nEnter your choice: "; cin >> choice;
		if (!CheckCin())
			continue;
		cout << endl;

		if (choice >= 1 && choice <= 4)
		{
			switch (choice)
			{
			case 1: SortByAgeWithoutChanging(participants, size, max_name);
				PressEnterToContinue();
				break;
			case 2: SearchByAge(participants, size, max_name);
				break;
			case 3: SearchByGender(participants, size, max_name);
				PressEnterToContinueAfterIgnore();
				break;
			case 4: back = true;
				break;
			}
		}
		else {
			cout << "No such choice!" << endl;
			PressEnterToContinue();
		}
		system("cls");
	} while (!back);
}
void SortByAgeWithoutChanging(Participants participants[], int size, int max_name)
{
	Participants temp_participants[max_participants_size];
	for (int i = 0; i < size; i++)
		temp_participants[i] = participants[i];

	SortByAge(temp_participants, size);
	Output(size, max_name);
}
void SearchByAge(Participants participants[], int size, int max_name)
{
	int target_age; bool found = false;
	cout << "Age: "; cin >> target_age;
	if (!CheckCin())
		return;
	cout << endl;

	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	for (int i = 0; i < size; i++)
	{
		if (participants[i].age == target_age)
		{
			found = true;
			BodyOfTable(participants, size, max_name, i);
		}
	}

	if (!found)
		cout << "No participant is this age." << endl;
	PressEnterToContinue();
}
void SearchByGender(Participants participants[], int size, int max_name)
{
	char target_gender[7]; bool found = false;
	cout << "Gender: "; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin.getline(target_gender, 7);
	cout << endl;

	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	for (int i = 0; i < size; i++)
	{
		if (strcmp(target_gender, participants[i].gender) == 0)
		{
			found = true;
			BodyOfTable(participants, size, max_name, i);
		}
	}

	if (!found)
		cout << "No participant is this gender." << endl;
}



void HeaderRowOfTable(int max_name)
{
	cout << "+"; for (int i = 0; i < no_column_width; i++) cout << "-";
	cout << "+"; for (int i = 0; i < max_name + 2; i++) cout << "-"; cout << "+"; for (int i = 0; i < age_column_width; i++) cout << "-";
	cout << "+"; for (int i = 0; i < results_column_width; i++) cout << "-"; cout << "+" << endl;
}
void TitleRowOfTable(int max_name)
{
	cout << "| No. |" << setw(max_name + 2) << left << " Name" << "| Age | Results |" << endl;
}
void BodyOfTable(Participants* participant, int size, int max_name, int i)
{
	cout << fixed << setprecision(2);
	cout << "| " <<
		setw(no_column_width - 2) << right << participant->number << " | " <<
		setw(max_name + 1) << left << participant->name << "| " <<
		setw(age_column_width - 2) << right << participant->age << " | " <<
		setw(results_column_width - 2) << right << participant->results << " |" << endl;
	if (i != size - 1)
	{
		for (int j = 0; j < table_width_without_name + max_name + 2; j++)
			cout << "-";
		cout << endl;
	}
	else HeaderRowOfTable(max_name);
}

void CheckMaxName(Participants* participant, int& max_name)
{
	if (strlen(participant->name) > max_name)
		max_name = strlen(participant->name);
}
bool CheckParticipantsEntered(bool entered)
{
	if (!entered)
	{
		cout << "There are no entered participants!" << endl;
		PressEnterToContinue();
		return false;
	}
	return true;
}
void AutoInput(Participants* participant, int& size, int& max_name, bool& entered)
{
	char temp[10];

	ifstream in_file(text_file);
	if (!in_file)
	{
		cout << "Error opening file. No participants have been added." << endl;
		return;
	}
	while (!in_file.eof() && size < max_participants_size)
	{
		in_file >> temp;
		participant->number = atoi(temp);

		in_file.clear(); in_file.ignore(numeric_limits<streamsize>::max(), '\n');
		in_file.getline(participant->name, 80);
		CheckMaxName(participant, max_name);

		in_file >> temp;
		participant->age = atoi(temp);

		in_file >> temp;
		participant->results = atof(temp);

		size++;
		entered = true;
	}
	in_file.close();
}

Participants* insertAtEnd(Participants* head_ref, Participants* new_participant)
{
	Participants* new_node = new Participants;
	Participants* last = head_ref;

	new_node = new_participant;
	new_node->next = NULL;

	if (head_ref == NULL) {
		head_ref = new_node;
		return head_ref;
	}

	while (last->next != NULL)
		last = last->next;

	last->next = new_node;
	return head_ref;
}