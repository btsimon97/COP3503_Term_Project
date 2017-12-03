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
#include <cstring>
#include <ctime>
#include "../Appointments/Appointment.h"
#include "../Info_Management/Information_Management.h"
#include "../Info_Management/ScheduleManager.h"
#include "../People_Management/Worker.h"
/* End Include Definitions */

#ifndef UI_UI_H_
#define UI_UI_H_

std::string getDBPath()
{
	std::cout << "Welcome! To get started, please enter the full path to the database file you would like to open. \n";
	std::cout << "If the DB you specified does not exist, it will be created automatically.\n";
	std::cout << "Enter DB Path: ";
	std::string DBPath;
	std::cin >> DBPath;
	std::cout << "\n";
	return DBPath;
}

void setupDBConnection(std::string DBPath)
{
	if(verifyDBExists(DBPath) == false)
	{
		createNewDB(DBPath);
	}
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

void displayNewAppointmentMenu(std::string DBFilePath)
{
	std::cout << "Create a New Appointment \n";
	std::cout << "Please Enter the Name of the Employee Hosting the Appointment: ";
	std::string employeeName;
	std::cin >> employeeName;
	std::cout << "\n";
	int matchCount = countMatchingWorkers(DBFilePath,employeeName);
	if(matchCount >= 1)
	{
		Worker* searchResults[matchCount];
		findMatchingWorkers(DBFilePath,employeeName,searchResults);
		std::cout << "Worker Matches: \n";
		std:cout << "ID \t Name \n";
		for(int i=0;i<matchCount;i++)
		{
			std::cout << searchResults[i]->getWorkerID() << "\t" << searchResults[i]->getWorkerName() << "\n";
		}
		std::cout << "Please Enter the ID of the Matching Worker: ";
		int workerID;
		std::cin >> workerID;
		std::cout << "\n";
		int month; int day; int year;
		std::cout << "Please Enter the Two-Digit Month of the Appointment: ";
		std::cin >> month;
		std::cout << "\n";
		std::cout << "Please Enter the Two-Digit Day of the Appointment: ";
		std::cin >> day;
		std::cout << "\n";
		std::cout << "Please Enter the Four-Digit Year of the Appointment: ";
		std::cin >> year;
		std::cout << "\n";
		int usertime;
		std::cout << "Please Enter the Time of the Appointment in 24-hour format (Example: 1 PM would be 1300): ";
		std::cin >> usertime;
		std::cout << "\n";
		std::cout << "Is this Appointment being used to denote time off by the employee? (Y/N): ";
		char *response; std::cin >> response;
		bool isDayOff;
		if(response == "Y")
		{
			isDayOff = true;
			ScheduleManager::addAppointment(isDayOff,day,month,year,usertime,workerID,6666,DBFilePath);
		}
		else
		{
			isDayOff = false;
			std::cout << "Please Enter the Name of the Visitor: ";
			std::string visitorName;
			std::cin >> visitorName;
			std::cout << "\n";
			int matchCount = countMatchingVisitors(DBFilePath,visitorName);
			if(matchCount >= 1)
			{
				Visitor* searchResults[matchCount];
				findMatchingVisitors(DBFilePath,visitorName,searchResults);
				std::cout << "Visitor Matches: \n";
				std::cout << "ID \t Name \n";
				for(int i=0;i<matchCount;i++)
				{
					std::cout << searchResults[i]->getVisitorID() << "\t" << searchResults[i]->getVisitorName() << "\n";
				}
				std::cout << "Please Enter the ID of the Matching Visitor: ";
				int visitorID;
				std::cin >> visitorID;
				std::cout << "\n";
				ScheduleManager::addAppointment(isDayOff,day,month,year,usertime,workerID,visitorID,DBFilePath);
			}
			else
			{
				std::cout << "No Existing Visitors Matching that Name Were Found in the Database. \n";
				std::cout << "Would you like to create a new visitor with this information now? (Y/N): ";
				char *response; std::cin >> response; std::cout << "\n";
				if(response == "Y")
				{
					std::cout << "Please Enter the Name of the Visitor to Add: ";
					std::string visitorName; std::cin >> visitorName; std::cout << "\n";
					srand(time(NULL));
					int visitorID = std::rand();
					addNewVisitor(DBFilePath,visitorID,visitorName);
					ScheduleManager::addAppointment(isDayOff,day,month,year,usertime,workerID,visitorID,DBFilePath);
				}
			}
		}
	}
	else
	{
		std::cout << "No results found for the Employee Specified. Verify the Employee exists and try again.";
	}
}

void displayAppointmentCancelationMenu(std::string DBFilePath)
{
	std::cout << "Cancel An Appointment \n";
	std::cout << "Enter the Name of the Employee to Cancel the Appointment For: ";
	std::string employeeName;
	std::cin >> employeeName;
	std::cout << "\n";
	int matchCount = countMatchingWorkers(DBFilePath,employeeName);
	if(matchCount >= 1)
	{
		Worker* searchResults[matchCount];
		findMatchingWorkers(DBFilePath,employeeName,searchResults);
		std::cout << "Worker Matches: \n";
		std::cout << "ID \t Name \n";
		for(int i=0;i<matchCount;i++)
		{
			std::cout << searchResults[i]->getWorkerID() << "\t" << searchResults[i]->getWorkerName() << "\n";
		}
		std::cout << "Please Enter the ID of the Matching Worker: ";
		int workerID;
		std::cin >> workerID;
		std::cout << "\n";
		std::cout << "Please Enter the two-digit appointment month : ";
		int month; std::cin >> month; std::cout << "\n";
		std::cout << "Please Enter the two-digit appointment day : ";
		int day; std::cin >> day; std::cout << "\n";
		std::cout << "Please Enter the four-digit appointment year : ";
		int year; std::cin >> year; std::cout << "\n";
		std::cout << "Please Enter the appointment time in 24-hour time format (Example: 1 PM is 1300): ";
		int appointmentTime; std::cin >> appointmentTime; std::cout << "\n";
		ScheduleManager::cancelAppointment(day,month,year,appointmentTime,DBFilePath);
	}
	else
	{
		std::cout << "No results found for the Employee Specified. Verify the Employee exists and try again.";
	}
}

int displayAppointmentSearchMenu()
{
	std::cout << "Appointment Search \n";
	std::cout << "Select a Search Option: \n";
	std::cout << "1. Search by Appointment Date and Time \n";
	std::cout << "3. Search by Worker \n";
	std::cout << "4. Search by Visitor \n";
	std::cout << "Enter your selection: ";
	int choice; std::cin >> choice; std::cout << "\n";
	return choice;
}

int displayWorkerAppointmentSearchMenu()
{
	std::cout << "Worker Appointment Search \n";
	std::cout << "Select an Option: \n";
	std::cout << "1. Print a Worker's Appointments for a Specific Day \n";
	std::cout << "2. Print a Worker's Appointments for a Specific Week \n";
	std::cout << "3. Print all of a Worker's Appointments \n";
	int choice; std::cin >> choice; std::cout << "\n";
	return choice;
}

void displayVisitorAppointmentSearchMenu(std::string DBFilePath)
{

}

int displayEmployeeManagementMenu()
{
	std::cout << "Manage Employee Records \n";
	std::cout << "Select a Clerical Option: \n";
	std::cout << "1. Add a New Worker \n";
	std::cout << "2. Remove an Existing Worker \n";
	std::cout << "3. Search Employee List \n";
	std::cout << "Enter your selection: ";
	int choice; std::cin >> choice; std::cout << "\n";
	return choice;
}

int displayVisitorManagementMenu()
{
	std::cout << "Manage Visitor Records \n";
	std::cout << "Select a Clerical Option: \n";
	std::cout << "1. Add a New Visitor \n";
	std::cout << "2. Remove an Existing Visitor \n";
	std::cout << "3. Search Visitor List \n";
	std::cout << "Enter your selection: ";
	int choice; std::cin >> choice; std::cout << "\n";
	return choice;
}
#endif /* UI_UI_H_ */
