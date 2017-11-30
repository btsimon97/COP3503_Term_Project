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
 *
 *      All search functions return
 */

#ifndef INFO_MANAGEMENT_INFORMATION_MANAGEMENT_H_
#define INFO_MANAGEMENT_INFORMATION_MANAGEMENT_H_

/* BEGIN LINKAGE OF DEPENDENT LIBRARIES */
//#include "Libraries/SQLite/sqlite3.h"
//#include "Libraries/SQLite/sqlite3.c"
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>
#include <sqlite3.h>
#include <iostream>
#include <string>
#include "../Appointments/Appointment.cpp"
/* END LINKAGE OF DEPENDENT LIBRARIES */

bool verifyDBExists(const char DBFilePath)
{
	std::cout << "Checking that the Database at" << DBFilePath << " exists...";
	std::ifstream ifile(DBFilePath);
	return (bool)ifile;
}

void createNewDB(const char *DBFilePath)
{
	SQLite::Database db(DBFilePath,SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
	char *workerSQL = 	"CREATE TABLE WORKERS("  \
						"ID INT PRIMARY KEY UNIQUE NOT NULL," \
						"NAME TEXT NOT NULL," \
						"DAYS_AVAILABLE CHAR(13) NOT NULL," \
						"START_TIME TEXT NOT NULL," \
						"STOP_TIME TEXT NOT NULL);";
	db.exec(workerSQL);
	char *visitorSQL = 	"CREATE TABLE VISITORS(" \
						"ID INT PRIMARY KEY UNIQUE NOT NULL," \
						"NAME TEXT NOT NULL);";
	db.exec(visitorSQL);
	char *appointmentSQL = 	"CREATE TABLE APPOINTMENTS("  \
							"ID INT PRIMARY KEY UNIQUE NOT NULL," \
							"GUEST_NAME	TEXT NOT NULL," \
							"APPOINTMENT_DATE TEXT NOT NULL," \
							"APPOINTMENT_TIME TEXT NOT NULL," \
							"WORKER_ID INTEGER NOT NULL," \
							"VISITOR_ID INTEGER NOT NULL," \
							"VISITOR_LINK FOREIGN KEY (VISITOR_ID) REFERENCES VISITOR(ID)," \
							"WORKER_LINK FOREIGN KEY (WORKER_ID) REFERENCES WORKER(ID));";
	db.exec(appointmentSQL);
}


void addNewWorker(const char *DBFilePath,int id, char *name, char *days_available, int startHour, int startMinute, int stopHour, int stopMinute)
{
	SQLite::Database db(DBFilePath,SQLite::OPEN_READWRITE);
	char *workerCreation = "INSERT INTO WORKERS(ID,NAME,DAYS_AVAILABLE,START_TIME,STOP_TIME) " \
							"VALUES("+id+","+"\""+name+"\""+","+"'"+days_available+"'"+",\""+startHour+":"+startMinute+"\""+",\""+stopHour+":"+stopMinute+"\");";
	db.exec(workerCreation);
}

void addNewVisitor(const char *DBFilePath, int id, char *name)
{
	SQLite::Database db(DBFilePath,SQLite::OPEN_READWRITE);
	char *visitorCreation = "INSERT INTO WORKERS(ID,NAME,DAYS_AVAILABLE,START_TIME,STOP_TIME) " \
							"VALUES("+id+","+"\""+name+"\""");";
	db.exec(visitorCreation);
}

//TODO: Fix Appointment Creator to account for visitor link
void addNewAppointment(const char *DBFilePath,int id, char *guestName,char *appointmentDate,char *appointmentTime, int personID)
{
	SQLite::Database db(DBFilePath,SQLite::OPEN_READWRITE);
	char *appointmentCreation = "INSERT INTO APPOINTMENTS(ID,GUEST_NAME,APPOINTMENT_DATE,APPOINTMENT_TIME,PERSON_ID) " \
								"VALUES("+id+","+"\""+guestName+"\""+",\""+appointmentDate+"\","+"\""+appointmentTime+"\","+personID+");";
	db.exec(appointmentCreation);
}

void removeWorker(const char *DBFilePath, int workerID)
{
	SQLite::Database db(DBFilePath,SQLite::OPEN_READWRITE);
	char *workerRemoval = "DELETE FROM WORKERS WHERE ID="+workerID+";";
	db.exec(workerRemoval);
}

void removeVisitor(const char *DBFilePath, int visitorID)
{
	SQLite::Database db(DBFilePath,SQLite::OPEN_READWRITE);
	char *visitorRemoval = "DELETE FROM VISITORS WHERE ID="+visitorID+";";
	db.exec(visitorRemoval);
}

void removeAppointment(const char *DBFilePath, int appointmentID)
{
	SQLite::Database db(DBFilePath,SQLite::OPEN_READWRITE);
	char *appointmentRemoval = "DELETE FROM APPOINTMENTS WHERE ID="+appointmentID+";";
	db.exec(appointmentRemoval);
}

int countMatchingWorkers(const char *DBFilePath, char *workerName)
{
	int matchingRecords = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement workerSearch(db,"SELECT * FROM WORKERS WHERE NAME LIKE ?");
	char *searchParam = "'%"+workerName+"%'";
	workerSearch.bind(1,searchParam);
	while(workerSearch.executeStep())
	{
		matchingRecords++;
	}
	return matchingRecords;
}

void findMatchingWorkers(const char *DBFilePath, char *workerName, Worker *resultsArray[])
{
	int matches = countMatchingWorkers(DBFilePath,workerName);
	int currentIndex = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement personSearch(db,"SELECT * FROM PEOPLE WHERE NAME LIKE ?");
	char *searchParam = "'%"+workerName+"%'";
	personSearch.bind(1,searchParam);
	while(personSearch.executeStep() && currentIndex < matches)
	{
		int id = personSearch.getColumn(0);
		resultsArray[currentIndex] = id;
		currentIndex++;
	}
}

int countMatchingAppointments(const char *DBFilePath,int personID, char *appointmentDate)
{

}

int countMatchingAppointments(const char *DBFilePath, int personID, char *appointmentDate, char *appointmentTime)
{

}

int countMatchingAppointments(const char *DBFilePath, char *appointmentDate)
{

}

int countMatchingAppointments(const char *DBFilePath, char *appointmentDate, char *appointmentTime)
{

}

void findAppointments(const char *DBFilePath, int personID, char *appointmentDate, Appointment *resultsArray[])
{

}

void findAppointments(const char *DBFilePath, int personID, char *appointmentDate, char *appointmentTime, Appointment *resultsArray[])
{

}
#endif /* INFO_MANAGEMENT_INFORMATION_MANAGEMENT_H_ */
