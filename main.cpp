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
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
				}
				break;
				case 4:
					switch(displayEmployeeManagementMenu())
					{
						case 1:
							break;
						case 2:
							break;
						case 3:
							break;
					}
					break;
				case 5:
					switch(displayVisitorManagementMenu())
					{
						case 1:
							break;
						case 2:
							break;
						case 3:
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
