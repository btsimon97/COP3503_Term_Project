#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H
#include "Appointment.h"
#include "Worker.h"
#include "Visitor.h"
#include <cstring>
using namespace std;
class ScheduleManager{
public:
	void addAppointment(bool offDay, int day, int month, int year, int appointmentTime, Worker* worker, string name, int id, const char* DBFilePath);
	void cancelAppointment(int day, int month, int year, int appointmentTime, const char* DBFilePath);
	void printWorkerWeekSchedule(Worker* worker, const char* DBFilePath);
	void printWorkerDaySchedule(Worker* worker, int day, int month, int year, const char* DBFilePath);
	void removeWorker(Worker* worker);
	void addWorker(Worker* worker);
private: 
	//Check the number of digits in a given integer. Used to check validity of day and year inputs.
	int numberOfDigits(int i);
	void chronologicalSort(Appointment** unsorted, int unsortedSize);
	int daysInMonth(int month);
};
#endif /* SCHEDULEMANAGER_H */
