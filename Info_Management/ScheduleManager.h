/*
Author: J Sheldon
Description: Functions to check validity of workers and appointments before writing them to a data base, removing from the data base, and printing.
*/
#include "Appointment.h"
#include "Worker.h"
#include "Visitor.h"
#include <cstring>

#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

using namespace std;
class ScheduleManager{
public:
	void addAppointment(bool offDay, int day, int month, int year, int appointmentTime, int workerID, int visitorID, string DBFilePath);
	void cancelAppointment(int day, int month, int year, int appointmentTime, string DBFilePath);
	void printWorkerWeekSchedule(int workerID, string DBFilePath);
	//Gets appointments for worker, date, and time.
	void printWorkerDaySchedule(int workerID, int day, int month, int year, string DBFilePath);
	//Print all of a worker's appointments.
	void printAllWorkerAppointments(int workerID, string DBFilePath);
	//Print all appointments at certain date and time.
	void printAppointmentsOnDateAndTime(int day, int month, int year, int appointmentTime, string DBFilePath);
	//Print all appointments for a visitor.
	void printVisitorAppointments(int visitorID, string DBFilePath);
	void fireWorker( string DBFilePath, int workerID);
	void addWorker(int workerID, string workerName, string daysAvailable, int startHour, int startMinute, int stopHour, int stopMinute, string DBFilePath);
	int appointmentIDGenerator();
private: 
	void chronologicalSort(Appointment** unsorted, int unsortedSize);
	int daysInMonth(int month, int year);
	//Do not want blank worker names.
	bool isBlank(string name);
};
#endif /* SCHEDULEMANAGER_H */
