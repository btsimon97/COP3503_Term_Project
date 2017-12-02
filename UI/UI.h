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
#include "../Appointments/Appointment.cpp"
#include "../Info_Management/Information_Management.h"
#include "../Info_Management/ScheduleManager.cpp"
#include "../People_Management/Worker.cpp"
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

void displayNewAppointmentMenu(const char *DBFilePath)
{
	std::cout << "Create a New Appointment \n";
	std::cout << "Please Enter the Name of the Employee Hosting the Appointment: ";
	std::string employeeName;
	std::cin >> employeeName;
	std::cout << "\n";
	char *cstr = new char [employeeName.length()+1];
	std::strcpy (cstr, employeeName.c_str());
	int matchCount = countMatchingWorkers(DBFilePath,cstr);
	if(matchCount >= 1)
	{
		Worker searchResults[matchCount];
		Worker *searchPointer[] = searchResults;
		findMatchingWorkers(DBFilePath,cstr,searchPointer);
		std::cout << "Worker Matches: \n";
		std:cout << "ID \t Name \n";
		for(int i=0;i<matchCount;i++)
		{
			std::cout << searchResults[i].getWorkerId() << "\t" << searchResults[i].getWorkerName() << "\n";
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
		int time;
		std::cout << "Please Enter the Time of the Appointment in 24-hour format (Example: 1 PM would be 1300): ";
		std::cin >> time;
		std::cout << "\n";
		std::cout << "Is this Appointment being used to denote time off by the employee? (Y/N): ";
		char response; std::cin >> response;
		bool isDayOff;
		if(response == "Y")
		{
			isDayOff = true;
			ScheduleManager::addAppointment(isDayOff,day,month,year,time,workerID,6666,DBFilePath);
		}
		else
		{
			isDayOff = false;
			std::cout << "Please Enter the Name of the Visitor: ";
			std::string visitorName;
			std::cin >> visitorName;
			std::cout << "\n";
			char *visitorChar = new char [visitorName.length()+1];
			std::strcpy (visitorChar, visitorName.c_str());
			int matchCount = countMatchingVisitors(DBFilePath,visitorChar);
			if(matchCount >= 1)
			{
				Visitor searchResults[matchCount];
				Visitor *searchPointer[] = searchResults;
				findMatchingVisitors(DBFilePath,cstr,searchPointer);
				std::cout << "Visitor Matches: \n";
				std:cout << "ID \t Name \n";
				for(int i=0;i<matchCount;i++)
				{
					std::cout << searchResults[i].getVisitorId() << "\t" << searchResults[i].getVisitorName() << "\n";
				}
				std::cout << "Please Enter the ID of the Matching Visitor: ";
				int visitorID;
				std::cin >> visitorID;
				std::cout << "\n";
				ScheduleManager::addAppointment(isDayOff,day,month,year,time,workerID,visitorID,DBFilePath);
			}
			else
			{
				std::cout << "No Existing Visitors Matching that Name Were Found in the Database. \n";
				std::cout << "Would you like to create a new visitor with this information now? (Y/N): ";
				char response; std::cin >> response; std::cout << "\n";
				if(response == "Y")
				{
					std::cout << "Please Enter the Name of the Visitor to Add: ";
					std::string visitorName; std::cin >> visitorName; std::cout << "\n";
					char *visitorCharName = new char [visitorName.length()+1];
					std::strcpy (visitorChar, visitorName.c_str());
					std::srand(std::time(NULL));
					int visitorID = std::rand();
					addNewVisitor(DBFilePath,visitorID,visitorCharName);
					ScheduleManager::addAppointment(isDayOff,day,month,year,time,workerID,visitorID,DBFilePath);
				}
			}
		}
	}
	else
	{
		std::cout << "No results found for the Employee Specified. Verify the Employee exists and try again.";
	}
}

#endif /* UI_UI_H_ */
