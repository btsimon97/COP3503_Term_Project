/*
 * main.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: bsimon
 *
 *      The Main Execution File for the Program. Program Flow is determined here, and all modules tie in here.
 */

/* Begin Include Directives */
#include <iostream>
#include <string>
#include <cstring>

#include "UI/UI.h"
/* End Include Directives */
int main()
{
	std::string DBPath = getDBPath();
	setupDBConnection(DBPath);
	int menuChoice;
	while(menuChoice != 7)
	{
		do
		{
			menuChoice = displayMainMenu();
		}
		while(menuChoice < 1 || menuChoice > 7);
		switch(menuChoice)
		{
			case 1:
				displayNewAppointmentMenu(DBPath);
				break;
			case 2:
				displayAppointmentCancelationMenu(DBPath);
				break;
			case 3:
				switch(displayAppointmentSearchMenu())
				{
					case 1:
						displayAppointmentDateAndTimeSearch(DBPath);
						break;
					case 2:
						switch(displayWorkerAppointmentSearchMenu())
						{
							case 1:
								displayWorkerDaySearchMenu(DBPath);
								break;
							case 2:
								displayWorkerWeekSearchMenu(DBPath);
								break;
							case 3:
								displayWorkerAppointmentDumpMenu(DBPath);
								break;
						}
						break;
					case 3:
						displayVisitorAppointmentSearchMenu(DBPath);
				}
				break;
				case 4:
					switch(displayEmployeeManagementMenu())
					{
						case 1:
                            addNewWorker(DBPath);
							break;
						case 2:
                            removeWorker(DBPath);
							break;
						case 3:
                            seachForWorker(DBPath);
							break;
					}
					break;
				case 5:
					switch(displayVisitorManagementMenu())
					{
						case 1:
                            displayNewVisitorMenu(DBPath);
							break;
						case 2:
                            displayRemoveVisitorMenu(DBPath);
							break;
						case 3:
                            displayVisitorSearchMenu(DBPath);
							break;
					}
					break;
				case 6:
					DBPath = getDBPath();
					setupDBConnection(DBPath);
					break;
				case 7:
					break;
		}
	}
}
