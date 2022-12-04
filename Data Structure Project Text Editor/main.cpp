#include<iostream>
#include<Windows.h>
#include<conio.h>
#include "TriTree.h"
using namespace std;
int main()
{

	//variables declartions
	TriTree obj;
	string *arr = NULL, str, str2;
	string alpha = "";
	char character = '/0';
	int count = 0;
	cout << "enter string" << endl;
	while (alpha != ";")
	{
		//using getch() function to read chracter
	label:
		if (count > 0)
		{

			cout << str2;
		}
		character = _getch();

		if (character == ';')
		{
			cout << " " << endl;
			break;
		}

		cout << character;

		//concatenating with string
		str += character;
		str2 = str;
		//checking if str.length()>=3 then it will show up the suggestions
		if (str.length() >= 3 && !(str[0] == ' ' || str[1] == ' ' || str[2] == ' '))
		{
			int no_of_suggestions = obj.Suggestion(str, arr);
			if (no_of_suggestions)
			{

				if (no_of_suggestions <= 10)
				{
					cout << "\t\t\t";
					for (int i = 0;i < no_of_suggestions;i++)
					{
						//outputs those suggestion whose size is 8 or less
						if (arr[i].length() <= 8)
						{
							cout << arr[i] << endl;
							cout << "\t\t\t";
							count++;
						}
					}
					Sleep(10000);
					system("cls");
					goto label;
				}
				else
				{

					cout << "\t\t\t";
					for (int i = 0;i < 10;i++)
					{
						//outputs those suggestion whose size is 8 or less
						if (arr[i].length() <= 8)
						{
							cout << arr[i] << endl;
							cout << "\t\t\t";
							count++;
						}
					}
					Sleep(10000);
					system("cls");
					goto label;

				}
			}

			else
			{
				cout << "\nsorry but the given word has no suggestion" << endl;
				return 0;
			}

		}


	}
	//system("pause");
	return 0;
}