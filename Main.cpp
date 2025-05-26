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
	int results;
	Participants* next;
}*start = NULL;

const int max_participants_size = 30;
const char text_file[] = "participants.txt";

const int no_column_width = 5;
const int age_column_width = 5;
const int results_column_width = 9;
const int table_width_without_name = no_column_width + age_column_width + results_column_width;

void Input(int& size, int& max_name);

void Remove(int& size);

void Output(int max_name);


int binarySearch(Participants arr[], int x, int size);
void SearchByResult(int max_name);


void SortByAge(int max_name);
void BubbleSort();


void AdditionalFunctions(int max_name);

void SelectionSort(Participants array[], int size);
void SearchByAge(int max_name);

void InsertionSort(Participants array[], int size);
void SortByResult(int max_name);


void HeaderRowOfTable(int max_name);
void TitleRowOfTable(int max_name);
void BodyOfTable(Participants* participant, int max_name);
void BodyOfTableArray(Participants array[], int size, int max_name, int i);


void CheckMaxName(Participants* participant, int& max_name);
void AutoInput(int& size, int& max_name);


Participants* insertAtEnd(Participants* new_participant);
void swap(Participants* a, Participants* b);


int main()
{
	int choice;
	bool exit = false;

	int size = 0;
	int max_name = 0;

	AutoInput(size, max_name);
	do
	{
		cout << "Beauty contest" << endl;
		cout << endl;
		cout << "1. Add new participants;" << endl;
		cout << "2. Remove participants;" << endl;
		cout << "3. Display all participants;" << endl;
		cout << "4. Binary search by result;" << endl;
		cout << "5. Sort the participants in ascending order by their age;" << endl;
		cout << "6. Additional actions;" << endl;
		cout << "7. Exit." << endl;
		cout << "\nEnter your choice: "; cin >> choice;

		if (!CheckCin())
			continue;
		cout << endl;

		if (choice >= 1 && choice <= 7)
		{
			switch (choice)

			{
			case 1: Input(size, max_name);
				break;

			case 2: Remove(size);
				system("pause");
				break;

			case 3: if (CheckParticipantsEntered(size))
			{
				Output(max_name);
				system("pause");
			}
				  break;

			case 4: if (CheckParticipantsEntered(size))
			{
				SearchByResult(max_name);
				system("pause");
			}
				  break;

			case 5: if (CheckParticipantsEntered(size))
			{
				SortByAge(max_name);
				BubbleSort();
				system("pause");
			}
				break;


			case 6: if (CheckParticipantsEntered(size))
			{
				system("cls");
				AdditionalFunctions(max_name);
			}
				  break;

			case 7: exit = true;
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
			insertAtEnd(new_participant);

			cout << endl;
			size++;
		}
	}
}

void Remove(int& size)
{
	char wanted_name[80];
	cout << "Enter the name of the participant to be removed: "; ClearBuffer();
	cin.getline(wanted_name, 80);

	Participants* temp = start;
	Participants* prev = NULL;

	if (temp != NULL && strcmp(temp->name, wanted_name) == 0)
	{
		start = temp->next;
		size--;
		delete temp;
		return;
	}

	while (temp != NULL && strcmp(temp->name, wanted_name) != 0)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL)
	{
		cout << "The element is not present in the list!" << endl;
		return;
	}

	cout << wanted_name << " has been successfully removed from the list.\n" << endl;
	prev->next = temp->next;
	size--;

	delete temp;
}

void Output(int max_name)
{
	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	Participants* temp = start;
	while (temp != NULL)
	{
		BodyOfTable(temp, max_name);
		temp = temp->next;
	}
}

int binarySearch(Participants arr[], int x, int size) 
{
	int low = 0;
	int high = size - 1;

	while (low <= high) 
	{
		int mid = (low + high) / 2; 

		if (x == arr[mid].results)
			return mid;
		else if (x > arr[mid].results)
			low = mid + 1;
		else
			high = mid - 1;
	}

	return -1;
}
void SearchByResult(int max_name)
{
	Participants* temp = start;
	Participants participants_array[max_participants_size]; int size = 0;

	while (temp != NULL)
	{
		participants_array[size] = *temp;
		temp = temp->next;
		size++;
	}

	Participants bf;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (participants_array[i].results > participants_array[j].results)
			{
				bf = participants_array[i];
				participants_array[i] = participants_array[j];
				participants_array[j] = bf;
			}
		}
	}

	int target_result;

	cout << "Result: "; cin >> target_result;
	ClearBuffer();
	if (!CheckCin())
		return;
	cout << endl;

	int result = binarySearch(participants_array, target_result, size);

	if (result != -1)
	{
		HeaderRowOfTable(max_name);
		TitleRowOfTable(max_name);
		HeaderRowOfTable(max_name);
		BodyOfTableArray(participants_array, size, max_name, result);
	}
	else cout << "No participant with this result was found!" << endl;
}


void SortByAge(int max_name)
{
	Participants array[10];
	Participants* temp = start;

	for (int i = 0; i < 10; i++)
	{
		if (temp == NULL)
		{
			cout << "Not enough participants to be sorted!" << endl;
			return;
		}

		array[i] = *temp;
		temp = temp->next;
	}

	Participants bf;
	for (int i = 0; i < 9; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (array[i].age > array[j].age)
			{
				bf = array[i];
				array[i] = array[j];
				array[j] = bf;
			}
		}
	}

	cout << "First 10 participants sorted by age:" << endl;
	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	for (int i = 0; i < 10; i++)
		BodyOfTableArray(array, 10, max_name, i);
}
void BubbleSort()
{
	if (start == NULL || start->next == NULL)
		return;

	bool swapped;
	Participants* current;
	Participants* prev;
	Participants* temp;

	do 
	{
		swapped = false;
		prev = NULL;
		current = start;

		while (current != NULL && current->next != NULL) 
		{
			if (current->age > current->next->age) 
			{
				temp = current->next;
				current->next = temp->next;
				temp->next = current;

				if (prev == NULL)
					start = temp;
				else 
					prev->next = temp;

				prev = temp;
				swapped = true;
			}
			else 
			{
				prev = current;
				current = current->next;
			}
		}
	} while (swapped);
}



void AdditionalFunctions(int max_name)
{
	int choice; bool back = false;
	do
	{
		cout << "1. Search by age;" << endl;
		cout << "2. Search by result;" << endl;
		cout << "3. Back" << endl;
		cout << "\nEnter your choice: "; cin >> choice;
		if (!CheckCin())
			continue;
		cout << endl;

		if (choice >= 1 && choice <= 3)
		{
			switch (choice)
			{
			case 1: SearchByAge(max_name);
				system("pause");
				break;
			case 2: SortByResult(max_name);
				system("pause");
				break;
			case 3: back = true;
				break;
			}
		}
		else 
			cout << "No such choice!" << endl;
		system("cls");
	} while (!back);
}

void SelectionSort(Participants array[], int size) 
{
	for (int step = 0; step < size - 1; step++) 
	{
		int min_idx = step;
		for (int i = step + 1; i < size; i++) 
		{
			if (array[i].age < array[min_idx].age)
				min_idx = i;
		}
		swap(&array[min_idx], &array[step]);
	}
}
void SearchByAge(int max_name)
{
	int target_age; bool found = false; 
	Participants correct_age[max_participants_size]; int age_arr_size = 0;

	cout << "Age over: "; cin >> target_age;
	ClearBuffer();
	if (!CheckCin())
		return;
	cout << endl;

	Participants* temp = start;
	while (temp != NULL)
	{
		if (temp->age >= target_age)
		{
			if (age_arr_size == 0)
				found = true;
			correct_age[age_arr_size] = *temp;
			age_arr_size++;
		}
		temp = temp->next;
	}
	SelectionSort(correct_age, age_arr_size);

	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	for (int i = 0; i < age_arr_size; i++)
		BodyOfTableArray(correct_age, age_arr_size, max_name, i);

	if (!found)
		cout << "No participant is this age." << endl;

}

void InsertionSort(Participants array[], int size) 
{
	for (int i = 1; i < size; i++) 
	{
		int j = i ;

		while (j > 0 && array[j - 1].results < array[j].results)
		{
			swap(&array[j - 1], &array[j]);
			j--;
		}
	}
}
void SortByResult(int max_name)
{
	int target_result; bool found = false;
	Participants correct_result[max_participants_size]; int result_arr_size = 0;

	cout << "Results over: "; cin >> target_result;
	ClearBuffer();
	if (!CheckCin())
		return;
	cout << endl;

	Participants* temp = start;
	while (temp != NULL)
	{
		if (temp->results >= target_result)
		{
			if (result_arr_size == 0)
				found = true;
			correct_result[result_arr_size] = *temp;
			result_arr_size++;
		}
		temp = temp->next;
	}
	InsertionSort(correct_result, result_arr_size);

	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	for (int i = 0; i < result_arr_size; i++)
	{
		BodyOfTableArray(correct_result, result_arr_size, max_name, i);
	}

	if (!found)
		cout << "No participant has result over " << target_result << "." << endl;
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
void BodyOfTable(Participants* participant, int max_name)
{
	cout << fixed << setprecision(2);
	cout << "| " <<
		setw(no_column_width - 2) << right << participant->number << " | " <<
		setw(max_name + 1) << left << participant->name << "| " <<
		setw(age_column_width - 2) << right << participant->age << " | " <<
		setw(results_column_width - 2) << right << participant->results << " |" << endl;
	HeaderRowOfTable(max_name);
}
void BodyOfTableArray(Participants array[], int size, int max_name, int i)
{
	cout << fixed << setprecision(2);
	cout << "| " <<
		setw(no_column_width - 2) << right << array[i].number << " | " <<
		setw(max_name + 1) << left << array[i].name << "| " <<
		setw(age_column_width - 2) << right << array[i].age << " | " <<
		setw(results_column_width - 2) << right << array[i].results << " |" << endl;
	HeaderRowOfTable(max_name);
}


void CheckMaxName(Participants* participant, int& max_name)
{
	if (strlen(participant->name) > max_name)
		max_name = strlen(participant->name);
}
void AutoInput(int& size, int& max_name)
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
		Participants* participant = new Participants;

		in_file >> temp;
		participant->number = atoi(temp);

		in_file.clear(); in_file.ignore(numeric_limits<streamsize>::max(), '\n');
		in_file.getline(participant->name, 80);
		CheckMaxName(participant, max_name);

		in_file >> temp;
		participant->age = atoi(temp);

		in_file >> temp;
		participant->results = atoi(temp);

		insertAtEnd(participant);
		size++;
	}
	in_file.close();
}


void swap(Participants* a, Participants* b)
{
	Participants temp = *a;
	*a = *b;
	*b = temp;
}
Participants* insertAtEnd(Participants* new_participant)
{
	Participants* last = start;
	new_participant->next = NULL;

	if (start == NULL) {
		start = new_participant;
		return start;
	}

	while (last->next != NULL)
		last = last->next;

	last->next = new_participant;
	return start;
}