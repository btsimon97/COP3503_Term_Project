/*
 * UI.h
 *
 *  Created on: Dec 1, 2017
 *      Author: bsimon
 *      This file defines UI functions to present the user facing interface and execute functions.
 */

/* Begin Include Definitions */
#include <iostream>
#include <string>
/* End Include Definitions */

#ifndef UI_UI_H_
#define UI_UI_H_

char *getDBPath()
{
	std::cout << "Welcome! To get started, please enter the full path to the database file you would like to open. \n";
	std::cout << "If the DB you specified does not exist, it will be created automatically.\n";
	std::cout << "Enter DB Path: ";
	char *DBPath;
	std::cin >> DBPath;
	std::cout << "\n";
	return DBPath;
}
int displayMainMenu()
{
	std::cout << "Welcome to CISE Appointment Management. Please Select From the Following Options: \n";
	std::cout << "1. Create a New Appointment \n";
	std::cout << "2. Cancel an Existing Appointment \n";
	std::cout << "3. Search Appointment Records \n";
	std::cout << "4. Manage Employee Records \n";
	std::cout << "5. Manage Visitor Records \n";
	std::cout << "6. Open a Different Appointment Database \n";
	std::cout << "7. Exit Program \n";
	std::cout << "\n" << "Enter your Selection: ";
	int choice = 9;
	std::cin >> choice;
	std::cout << "\n";
	return choice;
}



#endif /* UI_UI_H_ */
