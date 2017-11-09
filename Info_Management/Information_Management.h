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
	sqlite3_open(DBFilePath,db);
	peopleSQL = "CREATE TABLE PEOPLE("  \
	         "ID INT PRIMARY KEY UNIQUE NOT NULL," \
	         "NAME				TEXT		NOT NULL," \
	         "DAYS_AVAILABLE	CHAR(13)	NOT NULL," \
	         "START_TIME        TIME		NOT NULL," \
	         "STOP_TIME         TIME		NOT NULL);";
	peopleCreate = sqlite3_exec(db,peopleSQL);
	appointmentSQL = "CREATE TABLE APPOINTMENTS("  \
	         "ID INT PRIMARY KEY UNIQUE NOT NULL," \
	         "GUEST_NAME		TEXT		NOT NULL," \
	         "APPOINTMENT_DATE	DATE	NOT NULL," \
	         "APPOINTMENT_TIME	TIME		NOT NULL," \
	         "PERSON_ID         INTEGER		NOT NULL." \
			 "FOREIGN KEY(PERSON_ID) REFERENCES PEOPLE(ID));";
	appointmentsCreate = sqlite3_exec(db,appointmentSQL);
	sqlite3_close(db);
	return 0;
}

void connectToDB(sqlite *db,const char *dbFilePath)
{
	sqlite3_open(dbFilePath,db);
}

void disconnectDB(sqlite *db)
{
	sqlite3_close(db);
}
#endif /* INFO_MANAGEMENT_INFORMATION_MANAGEMENT_H_ */
