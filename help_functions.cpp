#include "help_functions.h"
#include <iostream>
using namespace std;

bool CheckParticipantsEntered(bool entered)
{
	if (!entered)
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
void PressEnterToContinue()
{
	cout << "\nPress Enter to continue";
	ClearBuffer();
	cin.get();
}
void PressEnterToContinueAfterIgnore()
{
	cout << "\nPress Enter to continue";
	cin.get();
}
void ClearBuffer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
