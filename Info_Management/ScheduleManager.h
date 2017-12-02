/*
Author: J Sheldon
Description: Functions to check validity of workers and appointments before writing them to a data base, removing from the data base, and printing.
*/

#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H
#include "Appointment.h"
#include "Worker.h"
#include "Visitor.h"
#include <cstring>
using namespace std;
class ScheduleManager{
public:
	void addAppointment(bool offDay, int day, int month, int year, int appointmentTime, string workerName, string name, int id, const char* DBFilePath);
	void cancelAppointment(int day, int month, int year, int appointmentTime, const char* DBFilePath);
	void printWorkerWeekSchedule(int workerID, const char* DBFilePath);
	void printWorkerDaySchedule(int workerID, int day, int month, int year, const char* DBFilePath);
	void fireWorker(const char *DBFilePath, int workerID);
	void addWorker(int workerID, string workerName, string daysAvailable, int startHour, int startMinute, int stopHour, int stopMinute, const char *DBFilePath);
	int appointmentIDGenerator();
private: 
	//Check the number of digits in a given integer. Used to check validity of day and year inputs.
	int numberOfDigits(int i);
	void chronologicalSort(Appointment** unsorted, int unsortedSize);
	int daysInMonth(int month);
	bool isBlank(string name);
};
#endif /* SCHEDULEMANAGER_H */
