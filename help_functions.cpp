#include "help_functions.h"
#include <iostream>
using namespace std;

bool CheckParticipantsEntered(int size)
{
	if (size < 1)
	{
		cout << "There are no entered participants!" << endl;
		system("pause");
		return false;
	}
	return true;
}
bool CheckCin()
{
	if (cin)
		return true;
	else
	{
		cout << "\nInvalid input!" << endl;
		system("pause");
		system("cls");
		return false;
	}
}
void ClearBuffer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
