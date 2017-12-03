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
#include "include/SQLiteCpp/Backup.h"
#include "include/SQLiteCpp/Column.h"
#include "include/SQLiteCpp/Database.h"
#include "include/SQLiteCpp/Exception.h"
#include "include/SQLiteCpp/Statement.h"
#include "include/SQLiteCpp/Transaction.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../Appointments/Appointment.h"
/* END LINKAGE OF DEPENDENT LIBRARIES */

bool verifyDBExists(std::string DBFilePath);

void createNewDB(std::string DBFilePath);


void addNewWorker(std::string DBFilePath,int id, std::string name, std::string days_available, int startHour, int startMinute, int stopHour, int stopMinute);

void addNewVisitor(std::string DBFilePath, int id, std::string name);

//TODO: Fix Appointment Creator to account for visitor link
void addNewAppointment(std::string DBFilePath,int id, std::string appointmentDate,int appointmentTime, int workerID, int visitorID, bool isDayOff);

void removeWorker(std::string DBFilePath, int workerID);

void removeVisitor(std::string DBFilePath, int visitorID);

void removeAppointment(std::string DBFilePath, int appointmentID);

int countMatchingWorkers(std::string DBFilePath, std::string workerName);

Worker* getWorker(std::string DBFilePath, int workerID);

void findMatchingWorkers(std::string DBFilePath, std::string workerName, Worker *resultsArray[]);

int countMatchingVisitors(std::string DBFilePath, std::string visitorName);

std::string getVisitorName(std::string DBFilePath,int visitorID);

void findMatchingVisitors(std::string DBFilePath, std::string visitorName, Visitor *resultsArray[]);

int countMatchingAppointments(std::string DBFilePath,int workerID, std::string appointmentDate);

int countMatchingAppointments(std::string DBFilePath, int entityID, bool searchByWorker);

int countMatchingAppointments(std::string DBFilePath, int workerID, std::string appointmentDate, int appointmentTime);

int countMatchingAppointments(std::string DBFilePath, std::string appointmentDate);

int countMatchingAppointments(std::string DBFilePath, std::string appointmentDate, int appointmentTime);

void findAppointments(std::string DBFilePath, int workerID, std::string appointmentDate, Appointment *resultsArray[]);

void findAppointments(std::string DBFilePath, int workerID, std::string appointmentDate, int appointmentTime, Appointment *resultsArray[]);

void findAppointments(std::string DBFilePath, int entityID, bool searchByWorker, Appointment *resultsArray[]);

void findAppointments(std::string DBFilePath, std::string appointmentDate, int appointmentTime, Appointment *resultsArray[]);

#endif /* INFO_MANAGEMENT_INFORMATION_MANAGEMENT_H_ */
