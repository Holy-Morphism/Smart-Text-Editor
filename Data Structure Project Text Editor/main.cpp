#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include<conio.h>
#include "TriTree.h"
#include"Huffman.h"
using namespace std;
int main()
{
	//variables declartions

	TriTree obj;
	char start_program;
	string *arr = NULL, CurrentString, String_On_Console, Final_string = "", encryptd_string, decrypt_string, catch_string;
	string alpha = "";
	char character = '/0', move_suggestion, get_suggestion;
	int count = 0, count2 = 0;
	
	
	ofstream write;
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	system("color 79");
	cout << "           *********************************SMART TEXT EDITOR****************************************" << endl;
	cout << "               PROGRAMMED BY: SUFIYAN-YOUNIS(21F-9242) OM-PARKASH(21F9272) ADEEL-TAHIR(21F-9258)";
	cout << endl;
	start_program = _getch();
	if (int(start_program)==13)
	{
		system("cls");
	}
	else
	{
		return 0;
	}
		system("color 70");
	cout << "1.Do You Want To edit Your Previous File\n2.Do You Want To Create NEW File" << endl;
	int n;
	cin >> n;
	if (n == 1)
	{
		CurrentString = "";
		String_On_Console = "";
		ifstream read("File.txt");
		getline(read, encryptd_string);
		string out = decoder(encryptd_string);
		for (int i = 0;i < out.length();i++)
		{
			if (out[i] == '#')
			{
				String_On_Console += '\n';
				cout << endl;
				i++;
			}
			cout << out[i];
			String_On_Console += out[i];
		}
		read.close();
		
		goto label;
	}
	else
		system("cls");
	cout << "enter string" << endl;
	while (alpha != ";")
	{
		//using getch() function to read chracter
	label:

		character = _getch();

		//if user enter spaces it will initialzed CurrentString with NULL and concatenates space with String_On_Console
		if (character == ' ')
		{
			CurrentString = "";
			String_On_Console += " ";
			//after that it will move back to where we start
			//cout << String_On_Console;
			cout << character;
			goto label;
		}
		//if character value matches then string will load into file and program ends
 		if (character == '=')
		{
			
			//converting string or text in binary code
			write.open("File.txt");
			if (Final_string != ""  && Final_string.length()==String_On_Console.length())
			{
				encryptd_string = encoder(Final_string);
			}
			else if (Final_string != ""  && Final_string.length() != String_On_Console.length())
			{
				for (int i = 0;i < String_On_Console.length();i++)
				{
					if (String_On_Console[i] == Final_string[i])
					{
						continue;
					}
					else
					{
						while (i < String_On_Console.length())
						{
							Final_string += String_On_Console[i];
							i++;
						}

					}
				}
				encryptd_string = encoder(Final_string);
			}
			else
			{
				encryptd_string = encoder(String_On_Console);
			}
				write << encryptd_string;
				write.close();
				system("cls");
				goto closing;
			
		}
		//this if condition is basically all for printing full stop so user can finish its sentence
		if (character == '.')
		{
			
			CurrentString = "";
			String_On_Console += ".";
			String_On_Console += " ";
			goto label;
		}
		//this will prompt string in new line also
 		if (int(character) == 13)
		{
			cout << endl;
			CurrentString = "";
			//this loop comparing characters by characters and will not concatenate the previous characters
			//this loop is basically used if user wants to enter in new line and want to save in file
			for (int i = 0;i < String_On_Console.length();i++)
			{
				if (String_On_Console[i] == Final_string[i])
				{
					continue;
				}
				else
				{
					while (i < String_On_Console.length())
					{
						Final_string += String_On_Console[i];
						i++;
					}
					break;
				}
			}
			//this hash is used to detect where user pressed the enter key
			Final_string += "#";
			String_On_Console += "\n";
			
			
			goto label;
		}
		//it will display your input on console/Screen
		cout << character;
		//concatenating with string
		CurrentString += character;
		String_On_Console += character;
		//checking if string is proper noun then it will show no suggestions
		if (int(CurrentString[0]) >= 65 && int(CurrentString[0]) <= 90)
		{
			int i = 0;
			//this is from when user enters proper noun it will not show the suggestions
			//loop is only used to complete its sentence.
			while(CurrentString[i]!=' ')
			{
				character = _getch();
				cout << character;
				CurrentString += character;
				String_On_Console += character;
				i++;
			}
			CurrentString = "";

			goto label;
		}
		//checking if CurrentString.length()>=2 then it will show up the suggestions
		if (CurrentString.length() >= 2 && !(CurrentString[0] == ' ' || CurrentString[1] == ' '))
		{
			int no_of_suggestions = obj.Suggestion(CurrentString, arr);
			if (no_of_suggestions)
			{

				if (no_of_suggestions <= 10)
				{
				for(int i=0;i<8;i++)
					cout << endl << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t";

					//loop for showing suggestions
					for (int i = 0;i < no_of_suggestions;i++)
					{
						
						cout << i << ". " << arr[i] << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t";
						
					}
					//this will prompt input from user to pick any word from suggetsion and if user doesnt want to pick any suggestion and want to continue, user will enter -1 
					cout << endl;
					int j = 0;
					//loop for selecting suggestions
					for (int i = 0;i < no_of_suggestions;i++)
					{
						//this is used if user enters '/' more than 10 times it will continue editing by tranforming its flow
						if (j == 10)
						{
							goto breaks;
						}
						//detects the suggetsion in string
						catch_string = arr[i];
						//changing color
						SetConsoleTextAttribute(color, FOREGROUND_RED | BACKGROUND_INTENSITY);
						cout << catch_string;

					input2:

						move_suggestion = _getch();

						if (move_suggestion == '`')
						{
							goto breaks;
						}

						else if (move_suggestion == ';')
						{
							//stroing current string length
							while (!(count == CurrentString.length()))
							{
								//popping/clearing last elemenst in a string till current string length so that we can place the picked up suggestion on console
								String_On_Console.pop_back();
								count++;
							}
							//getting count back to 0
							count = 0;
							SetConsoleTextAttribute(color, 7);
							//concatenates the string on console with th picked up suggestion
							String_On_Console += arr[i];
						
							goto breaks;
						}
						else if (move_suggestion == '/')
						{
							//this is used to clear single line..it will move back to 1st location and will print space
							cout << "\r";
							for (int i = catch_string.length();i > 0;i--)
							{

								cout << " ";
							}
							cout << "\r";
							j++;
						}
						else
						{
							cout << endl;
							cout << "invalid input/n try again";
							cout << endl;
							goto input2;
						}
					}
					//sleep you that user can see the suggestions
					breaks:
					Sleep(200);
					system("cls");
					system("color 70");
					//printing on console
					cout << String_On_Console;

					goto label;
				}
				//this else if for when the suggestions are more than 10
				else
				{
					for(int i=0;i<8;i++)
					cout << endl << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t";
					
					for (int i = 0;i < 10;i++)
					{
						
						
						cout << i << ". " << arr[i] << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t";

					}
					//this will prompt input from user to pick any word from suggetsion and if user doesnt want to pick any suggestion and want to continue, user will enter -1 


					cout << endl;
					int j = 0;
					for (int i = 0;i < no_of_suggestions;i++)
					{
						if (j == 10)
						{
							goto breaks2;
						}
						
						catch_string = arr[i];
						SetConsoleTextAttribute(color, FOREGROUND_RED | BACKGROUND_INTENSITY);
						
						cout << catch_string;
					input:
						move_suggestion = _getch();
						
						if (move_suggestion == '`')
						{
							goto breaks2;
						}
						else if (move_suggestion == ';')
						{
							//storing current length on count
							while (!(count == CurrentString.length()))
							{
								//popping/clearing last elemenst in a string till current string length so that we can place the picked up suggestion on console
								String_On_Console.pop_back();
								count++;
							}
							//getting back to 0
							count = 0;
							SetConsoleTextAttribute(color, 15);
							String_On_Console += arr[i];
							goto breaks2;
						}
						else if (move_suggestion == '/')
						{
							cout << "\r";
							for (int i = catch_string.length();i > 0;i--)
							{

								cout << " ";
							}
							cout << "\r";
							j++;
						}
						else
						{
							cout << endl;
							cout << "invalid input/n try again";
							cout << endl;
							goto input;
						}
					}
				breaks2:
					Sleep(200);
					system("cls");
					system("color 70");
					//printing on console
					
					cout << String_On_Console;
					goto label;
				}
			}
			else
			{
				goto label;
			}
		}
	
	}

closing:
	int choice;
	cout << "1.Do You Want To Create a New File\n2.Do You Want To Edit Your File\n3.EXIT" << endl;
	cin >> choice;
	if (choice == 1)
	{
		system("cls");
		CurrentString = "";
		String_On_Console = "";
		goto label;
	}
	else if (choice == 2)
	{
		system("cls");
		ifstream reads("File.txt");
		getline(reads, encryptd_string);
		string decrypted_string = decoder(encryptd_string);
		for (int i = 0;i < decrypted_string.length();i++)
		{
			if (decrypted_string[i] == '#')
			{
				cout << endl;
				i++;
			}
			cout << decrypted_string[i];
		}
		reads.close();
		goto label;
	}
	else
//	system("pause");
	return 0;	
}
