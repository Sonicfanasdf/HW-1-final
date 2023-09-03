#pragma once
#include <iomanip>
#include <cmath> //absolute value 
#include <cctype> //for the toupper validation


void baseConverterMenu(); //Part 2 Main menu
char baseConverterMenuOption(); //Introduction UI
int newIntInput(); // Option 1 in UI
void baseConversionSingle(int num1); //Option 2 in UI
void baseConversionAll(int num1); // Option 3 in UI
void menu();
void chooseOption();


//This is the Main menu for Part 2. It will return back to the Assignment 1 once it is done.
// Precondition: None
// Postcondition: returns nothing
void baseConverterMenu()
{
	int num1; //This is number that is used in all the calculations. 
	bool numInput = false; // this will prevent the program from runnning without an intergr placed in 
	do
	{
		switch (baseConverterMenuOption()) //this will call the main menu, the output a 
		{
		case '0': system("pause"); 
			system("cls");
			menu();
			chooseOption();
			break;
		case 'A':  num1 = newIntInput(); numInput = true; break;
		case 'B': if (!numInput) { cout << "ERROR - No integer has been entered."; break; } baseConversionSingle(num1); break;
		case 'C': if (!numInput) { cout << "ERROR - No integer has been entered."; break; } baseConversionAll(num1); break;
		default: cout << "ERROR - Invalid option. Please Enter A, B, C, or 0."; break;
		}
		cout << endl;
		system("pause");
	} while (true);
}

//This is the intro text for the Main Menu for Part 2
// Precondition: None
// Postcondition: Returns an uppercase of the option (char)
char baseConverterMenuOption()
{
	system("cls");
	cout << "CMPR131 Part 2. Base Converter" << endl;
	cout << "2: Base Converter" << endl;
	cout << string(100, char(205)) << endl;

	cout << "A. Enter an Integer Number (Base 10)" << endl;
	cout << "B. Specify the converting Base" << endl;
	cout << "C. Display All Converted Bases" << endl;
	cout << string(100, char(196)) << endl;

	cout << "0. Return" << endl;
	cout << string(100, char(205)) << endl;
	char option = toupper(inputChar("Option: "));
	return option;
}

//This is where to get the Number for the calculations 
// Precondition: User picks Option "1"
// Postcondition: Returns an Integer Positive for calculations on option 2 and 3
int newIntInput()
{
	return inputInteger("Enter An Integer in Base 10: ");
}

//This is where the user can choose what base to calculate their number. It is limited in range from binary [2] all the way to hexatrigesimal [36]
// Precondition: Valid Integer
// Postcondition: Returns the Integer and its converted Base
void baseConversionSingle(int num1)
{

	int base = inputInteger("Enter the base to convert your number to (2..36): ", 2, 36);
	string binaryNumber = "";
	char hex;
	int tempNum = num1;
	do
	{
		int remainder = abs(num1) % base;

		num1 /= base;

		if (remainder > 9)
		{
			hex = remainder + 55;
			string hexNum(1, hex);
			binaryNumber.insert(0, hexNum);
		}
		else
		{
			binaryNumber.insert(0, to_string(remainder));
		}

	} while (abs(num1) >= base);
	if (abs(num1) > 9)
	{
		hex = abs(num1) + 55;
		string hexNum(1, hex);
		binaryNumber.insert(0, hexNum);
		if (tempNum < 0)
		{
			binaryNumber.insert(0, "-");
		}
	}
	else if (num1 != 0)
	{
		binaryNumber.insert(0, to_string(num1));
	}


	cout << tempNum << " (Base of 10) = " << binaryNumber << " (Base of " << base << ")" << endl;
}

//This is where the program calculates their number in all the bases. It lists out all the base conversion from binary [2], to all the way to hexatrigesimal [36] in one list.
// Precondition: User pick Option "3"
// Postcondition: Outputs the Integer and the list of all converted Bases
void baseConversionAll(int num1)
{

	int tempNum = num1;
	char hex;
	cout << "Your number is " << num1 << "." << endl;
	string binaryNumber = "";
	for (int base = 2; base <= 36; base++)
	{
		num1 = tempNum;
		do
		{
			int remainder = abs(num1) % base;
			num1 /= base;
			if (remainder > 9)
			{
				hex = remainder + 55;
				string hexNum(1, hex);
				binaryNumber.insert(0, hexNum);
			}
			else
			{
				binaryNumber.insert(0, to_string(remainder));
			}
		} while (abs(num1) >= base);
		if (abs(num1) > 9)
		{
			hex = abs(num1) + 55;
			string hexNum(1, hex);
			binaryNumber.insert(0, hexNum);
			if (tempNum < 0)
			{
				binaryNumber.insert(0, "-");
			}
		}
		else if (num1 != 0)
		{
			binaryNumber.insert(0, to_string(num1));
		}

		cout << binaryNumber << " (Base of " << base << ")" << endl;
		binaryNumber.clear();
	}
}