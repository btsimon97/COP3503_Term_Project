#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H
#include "Appointment.h"
#include "Worker.h"
#include "Visitor.h"
#include <cstring>
using namespace std;
class ScheduleManager{
public:
	//Get dayLength in hours (easier for user) and convert to minutes. appointmentLength is in minutes to calculate appointmentSlotNumber.
	ScheduleManager(int appointmentLength);
	void addAppointment(bool offDay, int day, int month, int year, int timeSlot, Worker* worker, string name, int id, const char* DBFilePath);
	void cancelAppointment(string name, int id);
	void cancelAppointment(int day, int month, int year, int time);
	void printWorkerWeekSchedule(Worker* worker);
	void printWorkerDaySchedule(Worker* worker, int day, int month, int year, const char* DBFilePath);
	void scheduleNearestAppointment(string visitorName, int visitorID);
	void removeWorker(Worker* worker);
	void addWorker(Worker* worker);
private: 
	//Check the number of digits in a given integer. Used to check validity of day and year inputs.
	int numberOfDigits(int i);
	int appointmentLength;
};
#endif /* SCHEDULEMANAGER_H */
