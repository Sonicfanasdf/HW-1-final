#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <fstream>
#include <cmath>
#include "input.h"
#include "baseConverter.h"
#include "descrptiveStatistics.h"
#include "asciiConversion.h"

void menu();
void chooseOption();

int main()
{
	menu();
	chooseOption();
}

void menu() //main menu for program
{
	cout << "CMPR131 - Chapter 1 Software Development by Joe B\n";
	cout <<
		"==========================================================\n";
	cout << "\t1> ASCII Text To ASCII Numbers\n";
	cout << "\t2> Base Converter\n";
	cout << "\t3> Descriptive Statistics\n";
	cout << "----------------------------------------------------------\n";
	cout << "\t0> exit\n";
	cout <<
		"==========================================================\n";
}
void chooseOption() //chooses option for main menu
{
	do
	{
		int option = inputInteger("\tOption: ");

		switch (option)
		{
		case 0: exit(0);
			break;
		case 1: asciiMenu();
			break;
		case 2: baseConverterMenu();
			break;
		case 3: system("cls");
			descriptiveStatistics();
			break;
		default: cout << "ERROR-3A: Invalid input. Must be from 0..3.\n";
		}
	} while (true);
}