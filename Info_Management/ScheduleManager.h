/*
Author: J Sheldon
Description: Functions to check validity of workers and appointments before writing them to a data base, removing from the data base, and printing.
*/
#include "../Appointments/Appointment.h"
#include "../People_Management/Worker.h"
#include "../People_Management/Visitor.h"
#include "../Info_Management/Information_Management.h"
#include <cstring>

#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

using namespace std;
class ScheduleManager{
public:
	static void addAppointment(bool offDay, int day, int month, int year, int appointmentTime, int workerID, int visitorID, string DBFilePath);
	static void cancelAppointment(int day, int month, int year, int appointmentTime, string DBFilePath);
	static void printWorkerWeekSchedule(int workerID, string DBFilePath);
	//Gets appointments for worker, date, and time.
	static void printWorkerDaySchedule(int workerID, int day, int month, int year, string DBFilePath);
	//Print all of a worker's appointments.
	static void printAllWorkerAppointments(int workerID, string DBFilePath);
	//Print all appointments at certain date and time.
	static void printAppointmentsOnDateAndTime(int day, int month, int year, int appointmentTime, string DBFilePath);
	//Print all appointments for a visitor.
	static void printVisitorAppointments(int visitorID, string DBFilePath);
	static void fireWorker( string DBFilePath, int workerID);
	static void addWorker(int workerID, string workerName, string daysAvailable, int startHour, int startMinute, int stopHour, int stopMinute, string DBFilePath);
	static int appointmentIDGenerator();
private: 
	static void chronologicalSort(Appointment** unsorted, int unsortedSize);
	static int daysInMonth(int month, int year);
	//Do not want blank worker names.
	static bool isBlank(string name);
};
#endif /* SCHEDULEMANAGER_H */
