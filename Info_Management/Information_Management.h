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
							"APPOINTMENT_DATE TEXT NOT NULL," \
							"APPOINTMENT_TIME INT NOT NULL," \
							"WORKER_ID INTEGER NOT NULL," \
							"VISITOR_ID INTEGER," \
							"IS_DAY_OFF BOOLEAN NOT NULL," \
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
void addNewAppointment(const char *DBFilePath,int id,char *appointmentDate,int appointmentTime, int workerID, int visitorID, bool isDayOff)
{
	SQLite::Database db(DBFilePath,SQLite::OPEN_READWRITE);
	char *appointmentCreation = "INSERT INTO APPOINTMENTS(ID,APPOINTMENT_DATE,APPOINTMENT_TIME,WORKER_ID,VISITOR_ID,IS_DAY_OFF) " \
								"VALUES("+id+","+"\""+appointmentDate+"\","+appointmentTime+","+workerID+","+visitorID+","+isDayOff+");";
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

Worker getWorker(const char *DBFilePath, int workerID)
{
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement workerSelect(db,"SELECT * FROM WORKERS WHERE ID=?");
	workerSelect.bind(1,workerID);
	int id;
	char *name;
	char *daysAvailable;
	char *startTime;
	char *stopTime;
	while(workerSelect.executeStep())
	{
		id = workerSelect.getColumn("ID");
		name = workerSelect.getColumn("NAME");
		daysAvailable = workerSelect.getColumn("DAYS_AVAILABLE");
		startTime = workerSelect.getColumn("START_TIME");
		stopTime = workerSelect.getColumn("STOP_TIME");
	}
	Worker returner = new Worker(name,id); //TODO: Fix this once Worker class gets corrected.
	return returner;
}

void findMatchingWorkers(const char *DBFilePath, char *workerName, Worker *resultsArray[])
{
	int matches = countMatchingWorkers(DBFilePath,workerName);
	int currentIndex = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement workerSearch(db,"SELECT * FROM WORKERS WHERE NAME LIKE ?");
	char *searchParam = "'%"+workerName+"%'";
	workerSearch.bind(1,searchParam);
	while(workerSearch.executeStep() && currentIndex < matches)
	{
		int id = workerSearch.getColumn(0);
		resultsArray[currentIndex] = id;
		currentIndex++;
	}
}

int countMatchingVisitors(const char *DBFilePath, char *visitorName)
{
	int matchingRecords = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement visitorSearch(db,"SELECT * FROM VISITORS WHERE NAME LIKE ?");
	char *searchParam = "'%"+visitorName+"%'";
	visitorSearch.bind(1,searchParam);
	while(visitorSearch.executeStep())
	{
		matchingRecords++;
	}
	return matchingRecords;
}

std::string getVisitorName(const char *DBFilePath,int visitorID)
{
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement visitorSelect(db,"SELECT * FROM VISITORS WHERE ID=?");
	std::string name;
	visitorSelect.bind(1,visitorID);
	while(visitorSelect.executeStep())
	{
		name = visitorSelect.getColumn("NAME");
	}
	return name;
}

void findMatchingVisitors(const char *DBFilePath, char *visitorName, Visitor *resultsArray[])
{
	int matches = countMatchingVisitors(DBFilePath,visitorName);
	int currentIndex = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement visitorSearch(db,"SELECT * FROM VISITORS WHERE NAME LIKE ?");
	char *searchParam = "'%"+visitorName+"%'";
	visitorSearch.bind(1,searchParam);
	while(visitorSearch.executeStep() && currentIndex < matches)
	{
		int id = visitorSearch.getColumn("ID");
		std::string name = visitorSearch.getColumn("NAME");
		resultsArray[currentIndex] = new Visitor(id,name);
		currentIndex++;
	}
}

int countMatchingAppointments(const char *DBFilePath,int workerID, char *appointmentDate)
{
	int matchingRecords = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement appointmentSearch(db,"SELECT * FROM APPOINTMENTS WHERE WORKER_ID=? AND APPOINTMENT_DATE=?");
	appointmentSearch.bind(1,workerID);
	char *date = "\""+appointmentDate+"\"";
	appointmentSearch.bind(2,date);
	while(appointmentSearch.executeStep())
	{
		matchingRecords++;
	}
	return matchingRecords;
}

int countMatchingAppointments(const char *DBFilePath, int entityID, bool searchByWorker)
{
	int matchingRecords = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	if(searchByWorker == true)
	{
		SQLite::Statement appointmentSearch(db,"SELECT * FROM APPOINTMENTS WHERE WORKER_ID=?");
		appointmentSearch.bind(1,entityID);
		while(appointmentSearch.executeStep())
		{
			matchingRecords++;
		}
	}
	else
	{
		SQLite::Statement appointmentSearch(db,"SELECT * FROM APPOINTMENTS WHERE VISITOR_ID=?");
		appointmentSearch.bind(1,entityID);
		while(appointmentSearch.executeStep())
		{
			matchingRecords++;
		}
	}
	return matchingRecords;
}

int countMatchingAppointments(const char *DBFilePath, int workerID, char *appointmentDate, char *appointmentTime)
{
	int matchingRecords = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement appointmentSearch(db,"SELECT * FROM APPOINTMENTS WHERE WORKER_ID=? AND APPOINTMENT_DATE=? AND APPOINTMENT_TIME=?");
	appointmentSearch.bind(1,workerID);
	char *date = "\""+appointmentDate+"\"";
	appointmentSearch.bind(2,date);
	char *time = "\""+appointmentTime+"\"";
	appointmentSearch.bind(3,time);
	while(appointmentSearch.executeStep())
	{
		matchingRecords++;
	}
	return matchingRecords;
}

int countMatchingAppointments(const char *DBFilePath, char *appointmentDate)
{
	int matchingRecords = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement appointmentSearch(db,"SELECT * FROM APPOINTMENTS WHERE APPOINTMENT_DATE=?");
	char *date = "\""+appointmentDate+"\"";
	appointmentSearch.bind(1,date);
	while(appointmentSearch.executeStep())
	{
		matchingRecords++;
	}
	return matchingRecords;
}

int countMatchingAppointments(const char *DBFilePath, char *appointmentDate, char *appointmentTime)
{
	int matchingRecords = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement appointmentSearch(db,"SELECT * FROM APPOINTMENTS WHERE APPOINTMENT_DATE=? AND APPOINTMENT_TIME=?");
	char *date = "\""+appointmentDate+"\"";
	appointmentSearch.bind(1,date);
	char *time = "\""+appointmentTime+"\"";
	appointmentSearch.bind(2,time);
	while(appointmentSearch.executeStep())
	{
		matchingRecords++;
	}
	return matchingRecords;
}

void findAppointments(const char *DBFilePath, int workerID, char *appointmentDate, Appointment *resultsArray[])
{
	int matches = countMatchingAppointments(DBFilePath,workerID,appointmentDate);
	int currentIndex = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement appointmentSearch(db,"SELECT * FROM APPOINTMENTS WHERE WORKER_ID=? AND APPOINTMENT_DATE=?");
	appointmentSearch.bind(1,workerID);
	char *date = "\""+appointmentDate+"\"";
	appointmentSearch.bind(2,date);
	while(appointmentSearch.executeStep() && currentIndex<matches)
	{
		std::string date = appointmentSearch.getColumn("APPOINTMENT_DATE");
		int month = std::stoi(date.substr(0,2));
		int day = std::stoi(date.substr(2,2));
		int year = std::stoi(date.substr(5,4));
		int appointmentTime = appointmentSearch.getColumn("APPOINTMENT_TIME");
		int visitorID = appointmentSearch.getColumn("VISITOR_ID");
		std::string visitorName = getVisitorName(DBFilePath,visitorID);
		int workerID = appointmentSearch.getColumn("WORKER_ID");
		bool isDayOff = appointmentSearch.getColumn("IS_DAY_OFF");
		Worker linkedWorker = getWorker(DBFilePath,workerID);
		resultsArray[currentIndex] = new Appointment(isDayOff,day,month,year,appointmentTime,linkedWorker,visitorName,visitorID);
		currentIndex++;
	}
}

void findAppointments(const char *DBFilePath, int workerID, char *appointmentDate, char *appointmentTime, Appointment *resultsArray[])
{
	int matches = countMatchingAppointments(DBFilePath,workerID,appointmentDate,appointmentTime);
	int currentIndex = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	SQLite::Statement appointmentSearch(db,"SELECT * FROM APPOINTMENTS WHERE WORKER_ID=? AND APPOINTMENT_DATE=? AND APPOINTMENT_TIME=?");
	appointmentSearch.bind(1,workerID);
	char *date = "\""+appointmentDate+"\"";
	appointmentSearch.bind(2,date);
	char *time = "\""+appointmentTime+"\"";
	appointmentSearch.bind(3,time);
	while(appointmentSearch.executeStep() && currentIndex < matches)
	{
		std::string date = appointmentSearch.getColumn("APPOINTMENT_DATE");
		int month = std::stoi(date.substr(0,2));
		int day = std::stoi(date.substr(2,2));
		int year = std::stoi(date.substr(5,4));
		int appointmentTime = appointmentSearch.getColumn("APPOINTMENT_TIME");
		int visitorID = appointmentSearch.getColumn("VISITOR_ID");
		std::string visitorName = getVisitorName(DBFilePath,visitorID);
		int workerID = appointmentSearch.getColumn("WORKER_ID");
		bool isDayOff = appointmentSearch.getColumn("IS_DAY_OFF");
		Worker linkedWorker = getWorker(DBFilePath,workerID);
		resultsArray[currentIndex] = new Appointment(isDayOff,day,month,year,appointmentTime,linkedWorker,visitorName,visitorID);
		currentIndex++;
	}
}

void findAppointments(const char *DBFilePath, int entityID, bool searchByWorker, Appointment *resultsArray[])
{
	int matches = countMatchingAppointments(DBFilePath,entityID,searchByWorker);
	int currentIndex = 0;
	SQLite::Database db(DBFilePath,SQLite::OPEN_READONLY);
	if(searchByWorker == true)
	{
		SQLite::Statement appointmentSearch(db,"SELECT * FROM APPOINTMENTS WHERE WORKER_ID=?");
		appointmentSearch.bind(1,entityID);
		while(appointmentSearch.executeStep())
		{
			std::string date = appointmentSearch.getColumn("APPOINTMENT_DATE");
			int month = std::stoi(date.substr(0,2));
			int day = std::stoi(date.substr(2,2));
			int year = std::stoi(date.substr(5,4));
			int appointmentTime = appointmentSearch.getColumn("APPOINTMENT_TIME");
			int visitorID = appointmentSearch.getColumn("VISITOR_ID");
			std::string visitorName = getVisitorName(DBFilePath,visitorID);
			int workerID = appointmentSearch.getColumn("WORKER_ID");
			bool isDayOff = appointmentSearch.getColumn("IS_DAY_OFF");
			Worker linkedWorker = getWorker(DBFilePath,workerID);
			resultsArray[currentIndex] = new Appointment(isDayOff,day,month,year,appointmentTime,linkedWorker,visitorName,visitorID);
			currentIndex++;
		}
	}
	else
	{
		SQLite::Statement appointmentSearch(db,"SELECT * FROM APPOINTMENTS WHERE VISITOR_ID=?");
		appointmentSearch.bind(1,entityID);
		while(appointmentSearch.executeStep())
		{
			std::string date = appointmentSearch.getColumn("APPOINTMENT_DATE");
			int month = std::stoi(date.substr(0,2));
			int day = std::stoi(date.substr(2,2));
			int year = std::stoi(date.substr(5,4));
			int appointmentTime = appointmentSearch.getColumn("APPOINTMENT_TIME");
			int visitorID = appointmentSearch.getColumn("VISITOR_ID");
			std::string visitorName = getVisitorName(DBFilePath,visitorID);
			int workerID = appointmentSearch.getColumn("WORKER_ID");
			bool isDayOff = appointmentSearch.getColumn("IS_DAY_OFF");
			Worker linkedWorker = getWorker(DBFilePath,workerID);
			resultsArray[currentIndex] = new Appointment(isDayOff,day,month,year,appointmentTime,linkedWorker,visitorName,visitorID);
			currentIndex++;
		}
	}
}
#endif /* INFO_MANAGEMENT_INFORMATION_MANAGEMENT_H_ */
