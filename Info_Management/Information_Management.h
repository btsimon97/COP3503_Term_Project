/*
 * Information_Management.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Ben Simon
 *      This File Defines functions for managing the information used in the rest of the program.
 *      Primary functions consist of linking with an SQLite DB, and passing information to/from program to/from DB
 *      DB Maintenance and Setup Functions are Also Defined Here.
 *
 *      NOTE: This file defines primative DB routines for usage in other modules.
 *      The functions defined here, with one or two exceptions, should never be directly invoked by the main program.
 */

#ifndef INFO_MANAGEMENT_INFORMATION_MANAGEMENT_H_
#define INFO_MANAGEMENT_INFORMATION_MANAGEMENT_H_

/* BEGIN LINKAGE OF DEPENDENT LIBRARIES */
#include "Libraries/SQLite/sqlite3.h"
#include <iostream>
#include <string>

/* END LINKAGE OF DEPENDENT LIBRARIES */

bool verifyDBExists(const char DBFilePath)
{
	std::cout << "Checking that the Database at" << DBFilePath << " exists...";
	std::ifstream ifile(DBFilePath);
	return (bool)ifile;
}

int createNewDB(const char DBFilePath)
{
	std::cout << "Creating New DB File...";
	std::cout << "The following tables will be created: \n 1. People \n 2. Appointments";
	sqlite3 *db;
	int returnCode;
	char *errorMessage;
	returnCode = sqlite3_open(DBFilePath,db);
	char *peopleSQL = "CREATE TABLE PEOPLE("  \
	         "ID INT PRIMARY KEY UNIQUE NOT NULL," \
	         "NAME				TEXT		NOT NULL," \
	         "DAYS_AVAILABLE	CHAR(13)	NOT NULL," \
	         "START_TIME        TEXT		NOT NULL," \
	         "STOP_TIME         TEXT		NOT NULL);";
	returnCode = sqlite3_exec(db,peopleSQL,0,0,&errorMessage);
	char *appointmentSQL = "CREATE TABLE APPOINTMENTS("  \
	         "ID INT PRIMARY KEY UNIQUE NOT NULL," \
	         "GUEST_NAME		TEXT		NOT NULL," \
	         "APPOINTMENT_DATE	TEXT	NOT NULL," \
	         "APPOINTMENT_TIME	TEXT		NOT NULL," \
	         "PERSON_ID         INTEGER		NOT NULL." \
			 "FOREIGN KEY(PERSON_ID) REFERENCES PEOPLE(ID));";
	if(returnCode != SQLITE_OK)
	{
		std::cout<<"An Error Occurred While Setting up the People Table. Please use the following information for troubleshooting:\n";
		std::cout<< errorMessage;
		return returnCode;
	}
	returnCode= sqlite3_exec(db,appointmentSQL,0,0,&errorMessage);
	if(returnCode != SQLITE_OK)
		{
			std::cout<<"An Error Occurred While Setting up the Appointment Table. Please use the following information for troubleshooting:\n";
			std::cout<< errorMessage;
			return returnCode;
		}
	returnCode = sqlite3_close(db);
	if(returnCode != SQLITE_OK)
		{
			std::cout<<"An Error Occurred While Closing the DB. Please use the following information for troubleshooting:\n";
			std::cout<< errorMessage;
			return returnCode;
		}
	return returnCode;
}

void connectToDB(sqlite3 *db,const char *dbFilePath)
{
	sqlite3_open(dbFilePath,db);
}

void disconnectDB(sqlite3 *db)
{
	sqlite3_close(db);
}

int addNewPerson(int id, char *name, char *days_available, int startHour, int startMinute, int stopHour, int stopMinute)
{

}
#endif /* INFO_MANAGEMENT_INFORMATION_MANAGEMENT_H_ */
