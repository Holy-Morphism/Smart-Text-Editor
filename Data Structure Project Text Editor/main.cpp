#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include<conio.h>
#include "TriTree.h"
using namespace std;
int main()
{

	//variables declartions
	fstream File;
	File.open("File.txt", ios::out);
	int num;
	if (File)
	{
		cout << "File created successfully" << endl;

		//return 0;
	}
	else
	{
		cout << "File not created" << endl;
		//return 0;
	}
	TriTree obj;
	string *arr = NULL, str, str2;
	string alpha = "";
	char character = '/0';
	int count = 0, count2 = 0;
	cout << "enter string" << endl;
	while (alpha != ";")
	{
		//using getch() function to read chracter
	label:

		character = _getch();

		if (character == ' ')
		{
			str = "";
			str2 += " ";
			cout << " ";

			goto label;
		}
		if (character == '.')
		{

			str = "";
			str2 += ".";
			str2 += " ";
			goto label;
		}
		cout << character;

		//concatenating with string
		str += character;
		str2 += character;
		//checking if str.length()>=3 then it will show up the suggestions
		if (str.length() >= 2 && !(str[0] == ' ' || str[1] == ' ' || str[2] == ' '))
		{
			int no_of_suggestions = obj.Suggestion(str, arr);
			if (no_of_suggestions)
			{

				if (no_of_suggestions <= 10)
				{
					int j;
					cout << "\t\t\t";
					for (int i = 0;i < no_of_suggestions;i++)
					{
						//outputs those suggestion whose size is 8 or less
						if (arr[i].length() <= 8)
						{
							cout << i << ". " << arr[i] << endl;
							cout << "\t\t\t";
						}
					}
					cin >> num;
					if (num != -1)
					{
						while (!(count == str.length()))
						{
							str2.pop_back();
							count++;
						}
						count = 0;
						if (count2 == 0)
						{
							str2 = arr[num];
							count2++;
							goto breaks;
						}
						str2 += arr[num];
					}
				breaks:
					Sleep(900);
					system("cls");
					cout << str2;

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
							cout << i << ". " << arr[i] << endl;

							cout << "\t\t\t";

						}
					}
					cin >> num;
					if (num != -1)
					{
						while (!(count == str.length()))
						{
							str2.pop_back();
							count++;
						}
						count = 0;
						if (count2 == 0)
						{
							str2 = arr[num];
							count2++;
							goto breaks;
						}
						str2 += arr[num];
					}
					Sleep(900);
					system("cls");
					cout << str2;
					goto label;

				}
			}

			else
			{
				goto label;
			}

		}


	}
	//system("pause");
	return 0;
}
